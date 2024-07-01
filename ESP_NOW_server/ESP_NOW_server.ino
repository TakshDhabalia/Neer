#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "taksh";
const char* password = "12345678";
const char* thingspeakServer = "http://api.thingspeak.com";
const char* apiKey = "RL3EL6MU6Q6IG4ED";

WiFiClient client;
char receivedData[50];
bool newDataReceived = false;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register for a callback function that will be called when data is received
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);
}

// Callback function to handle received data
void onDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t len) {
  memcpy(receivedData, data, len);
  receivedData[len] = '\0';
  newDataReceived = true;

  Serial.print("Received Distance: ");
  Serial.print(receivedData);
  Serial.println(" cm");
}

void sendToThingSpeak(String value) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(thingspeakServer) + "/update?api_key=" + apiKey + "&field1=" + value;
    Serial.println("URL: " + url);  // Print the URL for debugging

    http.begin(client, url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("ThingSpeak Response: " + payload);
    } else {
      Serial.print("Error sending data to ThingSpeak. HTTP error code: ");
      Serial.println(httpCode);
    }
    http.end();
  } else {
    Serial.println("Error connecting to Wi-Fi");
  }
}

void loop() {
  if (newDataReceived) {
    sendToThingSpeak(receivedData);
    newDataReceived = false;
    delay(1000);  // Wait for 1 second before the next update
  }
}
