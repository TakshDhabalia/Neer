#include <ESP8266WiFi.h>
#include <espnow.h>

// Define pins for HC-SR04T and LEDs
#define TRIG_PIN 5  // GPIO5 (D1)
#define ECHO_PIN 4  // GPIO4 (D2)
#define STATUS_LED_PIN 14  // GPIO14 (D5)
#define CALIBRATION_LED_PIN 12  // GPIO12 (D6)
#define CONSTANT_SPEED_LED_PIN 13  // GPIO13 (D7)
#define COMMUNICATION_LED_PIN 15  // GPIO15 (D8)

// Server MAC Address
uint8_t serverAddress[] = {0x68, 0xC6, 0x3A, 0xE0, 0x7E, 0x5B};

void setup() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    digitalWrite(STATUS_LED_PIN, LOW);
    return;
  }
  
  // Register peer
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(serverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Initialize HC-SR04T sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LED pins
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(CALIBRATION_LED_PIN, OUTPUT);
  pinMode(CONSTANT_SPEED_LED_PIN, OUTPUT);
  pinMode(COMMUNICATION_LED_PIN, OUTPUT);

  // Indicate that the system is working well
  digitalWrite(STATUS_LED_PIN, HIGH);
  digitalWrite(CONSTANT_SPEED_LED_PIN, HIGH);
  digitalWrite(COMMUNICATION_LED_PIN, HIGH);

  // Send initial status to the server
  String initialStatus = "System initialized";
  esp_now_send(serverAddress, (uint8_t *)initialStatus.c_str(), initialStatus.length());
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  // Convert distance to string and send
  String distanceStr = String(distance);
  esp_now_send(serverAddress, (uint8_t *)distanceStr.c_str(), distanceStr.length());

  // Indicate that data is being sent
  digitalWrite(COMMUNICATION_LED_PIN, HIGH);
  delay(100); // Short blink
  digitalWrite(COMMUNICATION_LED_PIN, LOW);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(2000); // Send data every 2 seconds

  // Check ESP-NOW communication efficiency (dummy check for example)
  if (true) { // Replace with actual check condition
    digitalWrite(CONSTANT_SPEED_LED_PIN, HIGH);
  } else {
    digitalWrite(CONSTANT_SPEED_LED_PIN, LOW);
  }
}