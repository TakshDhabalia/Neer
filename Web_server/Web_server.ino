#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char* ssid = "taksh";
const char* password = "12345678";
const char* thingspeakServer = "api.thingspeak.com";
const char* apiKey = "0EXT8TLC3UWY00DS";

ESP8266WebServer server(80);
float distance = 0;

void setup() {
  Serial.begin(115200);
  delay(100); // Delay added for Serial Monitor to initialize
  
  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Start the HTTP server
  server.on("/update", handleUpdate);
  server.begin();  // Start the server

  // Print the IP address where the server can be accessed
  Serial.print("HTTP server started. Access it at: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.println("Ready to receive updates.");
}

void loop() {
  server.handleClient();

  // Update ThingSpeak every second if distance is greater than 0
  if (distance > 0) {
    if (updateThingSpeak(distance)) {
      distance = 0; // Reset distance after successful update
      Serial.println("ThingSpeak update successful");
    } else {
      Serial.println("ThingSpeak update failed");
    }
  }

  delay(1000);
}

void handleUpdate() {
  if (server.hasArg("distance")) {
    distance = server.arg("distance").toFloat();
    server.send(200, "text/plain", "Distance received");
    Serial.print("Distance received: ");
    Serial.println(distance);
  } else {
    server.send(400, "text/plain", "Invalid request");
    Serial.println("Invalid request");
  }
}

bool updateThingSpeak(float distance) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(thingspeakServer, 80)) {
      String postStr = "GET /update?api_key=";
      postStr += apiKey;
      postStr += "&field1=";
      postStr += String(distance);
      postStr += " HTTP/1.1\r\n";
      postStr += "Host: ";
      postStr += thingspeakServer;
      postStr += "\r\n";
      postStr += "Connection: close\r\n\r\n";

      client.print(postStr);
      Serial.println("Data sent to ThingSpeak");

      // Wait for response from ThingSpeak
      unsigned long timeout = millis();
      while (client.available() == 0) {
        if (millis() - timeout > 5000) {
          Serial.println("No response from ThingSpeak");
          client.stop();
          return false;
        }
      }

      // Read the response from ThingSpeak
      String response = client.readStringUntil('\r');
      Serial.print("Response from ThingSpeak: ");
      Serial.println(response);

      client.stop();
      return true;
    } else {
      Serial.println("Connection to ThingSpeak failed");
      return false;
    }
  } else {
    Serial.println("WiFi not connected");
    return false;
  }
}
