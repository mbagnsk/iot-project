#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESPDateTime.h>

const char* ssid = "*"; 
const char* password = "*";
 
const char* brokerAdress = "*"; 

WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  Serial.print("loop");
  delay(2000);
}
