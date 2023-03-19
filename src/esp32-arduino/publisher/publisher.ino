#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoMqttClient.h>
#include <ESPDateTime.h>
#include <ArduinoJson.h>
#include <String.h>

const char* ssid = "*"; 
const char* password = "*";
 
const char brokerAddress[] = "*";
const int mqttPort = 1884;

const String _messageXML = "message";
const String _deviceXML = "device";
const String _idDeviceXML = "idDevice";
const String _idChannelXML = "idChannel";
const String _idIoTHubXML = "idIoTHub";
const String _measurementXML = "measurement";
const String _idMeasurementXML = "idMeasurement";
const String _valueXML = "value";
const String _unitsXML = "units";
const String _measurementTypeXML = "measurementType";
const String _dateTimeXML = "dateTime";

const String _idDevice = "1";
const String _idChannel = "1";
const String _idIoTHub = "1";
const String _temperatureMeasurementType = "1";
const String _celsius = "1";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
int status = WL_IDLE_STATUS;

struct Measurement {
  String value;
  String units; 
  String measurementType;
  String datetime;
};

String createMessage(String idDevice, String idChannel, String idIoTHub, Measurement measurement){
  StaticJsonDocument<512> doc;
  String JSONmessageBuffer;
  JsonObject message = doc.createNestedObject(_messageXML);
  message[_deviceXML][_idDeviceXML] = idDevice;
  message[_deviceXML][_idChannelXML] = idChannel;
  message[_deviceXML][_idIoTHubXML] = idIoTHub;
  message[_measurementXML][_valueXML] = measurement.value;
  message[_measurementXML][_unitsXML] = measurement.units;
  message[_measurementXML][_measurementTypeXML] = measurement.measurementType;
  message[_measurementXML][_dateTimeXML] = measurement.datetime;
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
}

String getTemperature(){
  int temperature = random(15, 25);
  return String(temperature);
}

void loop() {
  Measurement temperatureMeasurement;
  temperatureMeasurement.value = getTemperature();
  temperatureMeasurement.units = _celsius;
  temperatureMeasurement.measurementType = _temperatureMeasurementType;
  temperatureMeasurement.datetime = DateTime.formatUTC("%Y-%m-%d %H:%M:%S");
  Serial.println(temperatureMeasurement.datetime);
  mqttPostTemperature(_idIoTHub, _idDevice, _idChannel, message);
  Serial.println(message);
  delay(5000);
}
