#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define TINY_GSM_MODEM_SIM900  // Define the GSM modem model before including the TinyGsmClient library
#include <TinyGsmClient.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

// WiFi credentials
const char* ssid = "taksh";
const char* password = "12345678";

// ThingSpeak credentials
const char* apiKey = "0EXT8TLC3UWY00DS";
const char* server = "api.thingspeak.com";

// GSM module pins and settings
#define MODEM_RST 14 // GPIO14 (D5 on some boards)
#define MODEM_PWRKEY 12 // GPIO12 (D6 on some boards)
#define MODEM_POWER_ON 13 // GPIO13 (D7 on some boards)
#define MODEM_TX 1  // GPIO1 (TX)
#define MODEM_RX 3  // GPIO3 (RX)
#define SerialMon Serial
SoftwareSerial SerialAT(MODEM_RX, MODEM_TX); // RX, TX

// HC-SR04 settings
#define TRIGGER_PIN 12  // GPIO12 (D6 on some boards)
#define ECHO_PIN 13     // GPIO13 (D7 on some boards)
#define MAX_DISTANCE 400 // Maximum distance to ping (in centimeters)
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// SMS settings
const char* phone_number = "+917715958053";
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

// Function to send SMS
void sendSMS(const char* number, const char* message) {
  modem.sendSMS(number, message);
}

void setup() {
  // Debugging serial
  SerialMon.begin(115200);

  // Initialize GSM module
  SerialAT.begin(9600);
  delay(3000); // Give time for GSM module to initialize

  // Restart SIM900 module
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(100);
  digitalWrite(MODEM_PWRKEY, HIGH);

  // Begin modem connection
  modem.restart();
  SerialMon.println("Modem: " + modem.getModemInfo());

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SerialMon.print(".");
  }
  SerialMon.println();
  SerialMon.println("WiFi connected");

  // Check GSM module communication
  if (!modem.init()) {
    SerialMon.println("GSM module not responding.");
    while (true);
  }
  SerialMon.println("GSM module initialized.");
}

void loop() {
  // Measure distance
  delay(100); // Wait 100ms between pings to ensure the sensor resets properly.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  float distance = uS / US_ROUNDTRIP_CM; // Convert time to distance in cm.

  SerialMon.print("Distance: ");
  SerialMon.print(distance);
  SerialMon.println(" cm");

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient wifiClient;
    HTTPClient http;
    String url = String("http://") + server + "/update?api_key=" + apiKey + "&field1=" + String(distance);
    http.begin(wifiClient, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      SerialMon.println("ThingSpeak response: " + payload);
    } else {
      SerialMon.println("Error sending data to ThingSpeak.");
    }
    http.end();
  } else {
    SerialMon.println("WiFi not connected.");
  }

  // Send SMS if distance is below threshold
  if (distance < 50) {
    String message = "Alert: Distance below threshold! Distance: " + String(distance) + " cm";
    sendSMS(phone_number, message.c_str());
    SerialMon.println("SMS sent.");
  }

  delay(1000); // Wait a second before next measurement
}
