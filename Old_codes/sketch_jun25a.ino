#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "taksh";
const char* password = "12345678";

IPAddress serverIP(192, 168, 210, 33); // IP address of the ESP8266 server
const int serverPort = 80; // Port on which the server is running

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  Serial.println("Ready to send data to server.");
}

void loop() {
  // Simulate sending distance data to server (replace with actual sensor data)
  float distance = random(0, 100); // Simulated distance data (0 to 99)

  // Send distance data to server
  if (sendDataToServer(distance)) {
    Serial.println("Data sent to server successfully");
  } else {
    Serial.println("Failed to send data to server");
  }

  delay(5000); // Send data every 5 seconds
}

bool sendDataToServer(float distance) {
  if (client.connect(serverIP, serverPort)) {
    Serial.print("Connected to server at ");
    Serial.print(serverIP);
    Serial.print(":");
    Serial.println(serverPort);

    String url = "/update?distance=" + String(distance);
    Serial.print("Sending data to server: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + serverIP.toString() + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Wait for response from server
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("No response from server");
        client.stop();
        return false;
      }
    }

    // Read response from server
    String response = client.readStringUntil('\r');
    Serial.print("Response from server: ");
    Serial.println(response);

    client.stop();
    return true;
  } else {
    Serial.println("Failed to connect to server");
    return false;
  }
}