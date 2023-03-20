#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoMqttClient.h>
#include <ESPDateTime.h>
#include <ArduinoJson.h>
#include <String.h>

const char* ssid = ""; 
const char* password = "";
 
const char brokerAddress[] = "192.168.1.54";
const int mqttPort = 1884;

const String _messageXML = "message";
const String _deviceXML = "device";
const String _idDeviceXML = "idDevice";
const String _idChannelXML = "idChannel";
const String _idIoTHubXML = "idIotHub";
const String _measurementXML = "measurement";
const String _idMeasurementXML = "idMeasurement";
const String _valueXML = "value";
const String _idUnitXML = "idUnit";
const String _measurementTypeXML = "measurementType";
const String _measurementDateTimeXML = "measurementDateTime";

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
  String measurementDatetime;
};

String createMessage(String idDevice, String idChannel, String idIoTHub, Measurement measurement){
  //  create a json message based on passed parameters
  //  message structure:
  // {
  //  "message": {
  //    "device": {
  //      "idDevice": idDevice,
  //      "idChannel": idChannel,
  //      "idIoTHub": idIoTHub
  //    }
  //    "measurement": {
  //      "value": measurement.value,
  //      "units": measurement.units,
  //      "measurementType": measurement.measurementType,
  //      "measurementDateTime": measurement.measurementDateTime
  //    }
  //  }
  // }
  // 
  // :param: idDevice: id of measuring device,
  // :param: idChannel: id of device's sensor channel
  // :param: idIoTHub: id of IoTHub that is a receivcer of message
  // :param: measurement: structure store details about measurement
  // :return: JSONmessageBuffer: string contains created message in json format
  
  StaticJsonDocument<512> doc;
  String JSONmessageBuffer;
  JsonObject message = doc.createNestedObject(_messageXML);
  message[_deviceXML][_idDeviceXML] = idDevice;
  message[_deviceXML][_idChannelXML] = idChannel;
  message[_deviceXML][_idIoTHubXML] = idIoTHub;
  message[_measurementXML][_valueXML] = measurement.value;
  message[_measurementXML][_idUnitXML] = measurement.units;
  message[_measurementXML][_measurementTypeXML] = measurement.measurementType;
  message[_measurementXML][_measurementDateTimeXML] = measurement.measurementDatetime;
  int JSONmessageSize = serializeJson(doc, JSONmessageBuffer);
  return JSONmessageBuffer;
}

void mqttPostTemperature(String idIoTHub, String idDevice, String idChannel, String message){
  // post passed message via mqtt on topic created basing on passed parameters       
  // ex. topic = "1/measurements/temperature/1/1"
  // :param: idDevice: id of measuring device,
  // :param: idChannel: id of device's sensor channel
  // :param: idIoTHub: id of IoTHub that is a receivcer of message

  const String mt = "/measurements/temperature/";
  
  char msg[1000];
  String topic = idIoTHub + mt + idDevice + "/" + idChannel;
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
  temperatureMeasurement.measurementDatetime = DateTime.formatUTC("%Y-%m-%d %H:%M:%S");
  String message = createMessage(_idDevice, _idChannel, _idIoTHub, temperatureMeasurement);
  mqttPostTemperature(_idIoTHub, _idDevice, _idChannel, message);
  delay(5000);
}
