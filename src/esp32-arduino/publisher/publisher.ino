#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoMqttClient.h>
#include <ESPDateTime.h>
#include <ArduinoJson.h>
#include <String.h>

const char* ssid = "Orange_Swiatlowod_E300"; 
const char* password = "kilocebuli";
 
const char brokerAddress[] = "192.168.1.54";
const int mqttPort = 1884;

const String _message = "message";
const String _device = "device";
const String _idDevice = "idDevice";
const String _idChannel = "idChannel";
const String _idIoTHub = "idIoTHub";
const String _measurement = "measurement";
const String _idMeasurement = "idMeasurement";
const String _value = "value";
const String _measurementType = "measurementType";
const String _dateTime = "dateTime";

String idDevice = "1";
String idChannel = "1";
String idIoTHub = "1";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
int status = WL_IDLE_STATUS;

struct Measurement {
  char* value;
  char* measurementType;
  char* datetime;
};

String createMessage(String idDevice, String idChannel, String idIoTHub, Measurement measurement){
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

void mqttPostTemperature(String idIoTHub, String idDevice, String idChannel, String message){
  char msg[1000];
  String topic = idIoTHub + "/" + idDevice + "/" + idChannel;
  message.toCharArray(msg, 1000);
  mqttClient.beginMessage(topic);
  mqttClient.print(msg);
  mqttClient.endMessage();
}

void setup() {  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  if (!mqttClient.connect(brokerAddress, mqttPort)){
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  Measurement measurement;
  measurement.value = "1";
  measurement.measurementType = "2";
  measurement.datetime = "2023-03-13";
  String message = createMessage(idDevice, idChannel, idIoTHub, measurement); 
  mqttPostTemperature(idIoTHub, idDevice, idChannel, message);
  delay(5000);
}
