// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/

#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(38400);
  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop(){

}
