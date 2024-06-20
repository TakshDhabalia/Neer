#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

AsyncWebServer server(80);

String distance = "No data";

void setup(){
  Serial.begin(115200);
  
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", distance.c_str());
  });
  
  server.begin();
}

void loop(){
}
