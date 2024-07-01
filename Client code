#include <ESP8266WiFi.h>
#include <espnow.h>

// Define pins for HC-SR04T
#define TRIG_PIN 5  // GPIO5 (D1)
#define ECHO_PIN 4  // GPIO4 (D2)

// Server MAC Address
uint8_t serverAddress[] = {0x68, 0xC6, 0x3A, 0xE0, 0x7E, 0x5B};

void setup() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(serverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Initialize HC-SR04T sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
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

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(2000); // Send data every 2 seconds
}
