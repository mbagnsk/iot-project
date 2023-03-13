#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESPDateTime.h>
#include <ArduinoJson.h>
#include <String.h>

const char* ssid = "*"; 
const char* password = "*";
 
const char* brokerAdress = "*";

const char* _message = "message";
const char* _device = "device";
const char* _idDevice = "idDevice";
const char* _idChannel = "idChannel";
const char* _idIoTHub = "idIoTHub";
const char* _measurement = "measurement";
const char* _idMeasurement = "idMeasurement";
const char* _value = "value";
const char* _measurementType = "measurementType";
const char* _dateTime = "dateTime";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;

struct Measurement {
  char* value;
  char* measurementType;
  char* datetime;
};

String createMessage(char* idDevice, char* idChannel, char* idIoTHub, Measurement measurement){
  StaticJsonDocument<256> doc;
  String JSONmessageBuffer;
  JsonObject message = doc.createNestedObject(_message);
  message[_device][_idDevice] = idDevice;
  message[_device][_idChannel] = idChannel;
  message[_device][_idIoTHub] = idIoTHub;
  message[_measurement][_value] = measurement.value;
  message[_measurement][_measurementType] = measurement.measurementType;
  message[_measurement][_dateTime] = measurement.datetime;
  int JSONmessageSize = serializeJson(doc, JSONmessageBuffer);
  return JSONmessageBuffer;
}

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
  Measurement measurement;
  measurement.value = "1";
  measurement.measurementType = "2";
  measurement.datetime = "2023-03-13";
  String message = createMessage("1", "2", "3", measurement); 
  Serial.print(message);
  delay(2000);
}
