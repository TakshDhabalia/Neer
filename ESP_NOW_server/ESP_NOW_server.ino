// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/
#include <ESP8266WiFi.h>
void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  Serial.println(WiFi.macAddress());
}
 
void loop(){
  Serial.println(WiFi.macAddress());
}