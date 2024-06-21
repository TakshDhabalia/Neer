#include <ESP8266WiFi.h>
#include <NewPing.h>

#define TRIGGER_PIN 12  // GPIO12 (D6)
#define ECHO_PIN 14     // GPIO14 (D5)
#define MAX_DISTANCE 400 // Maximum distance to ping (in centimeters)

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverIP = "server_IP_address"; // Replace with your server's IP address

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  Serial.println("Ultrasonic Sensor HR-SR04T with ESP8266");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(100); // Wait 100ms between pings to ensure the sensor resets properly.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  float distance = uS / US_ROUNDTRIP_CM; // Convert time to distance in cm.

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(serverIP, 80)) {
      client.print(String("GET /update?distance=") + distance + " HTTP/1.1\r\n" +
                   "Host: " + serverIP + "\r\n" + 
                   "Connection: close\r\n\r\n");
      delay(10);
    }
    client.stop();
  }

  delay(1000); // Wait a second before next measurement
}