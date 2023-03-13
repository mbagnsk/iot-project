# ESP32 JSON

It's possible to store data using JSON format on ESP8266.
ArduinoJson.h library enables to use JSON objects.

Example:

1. Creating JSONObject
```c
StaticJsonDocument<256> doc;
String JSONmessageBuffer;
```

2. Put some keys and values:
```c 
JsonObject message = doc.createNestedObject(_message);
message[_device][_idDevice] = idDevice;
message[_device][_idChannel] = idChannel;
message[_device][_idIoTHub] = idIoTHub;
message[_measurement][_value] = measurement.value;
message[_measurement][_measurementType] = measurement.measurementType;
message[_measurement][_dateTime] = measurement.datetime;
```

3. Result:
```
{
	"message":
	{
		"device":
		{
			"idDevice":"1",
			"idChannel":"2",
			"idIoTHub":"3"
		},
		"measurement":
		{
			"value":"1",
			"measurementType":"2",
			"dateTime":"2023-03-13"
		}
	}
}
```
 
4. Then it's possible to parse JSON object to string that would can be send via MQTT:
```c
int JSONmessageSize = serializeJson(doc, JSONmessageBuffer);
```

5. Publish message:
```c
WiFiClient espClient;
PubSubClient client(espClient);

if (client.publish("esp/test", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
} else {
    Serial.println("Error sending message");
}
client.loop();
```

source: https://techtutorialsx.com/2017/04/29/esp32-sending-json-messages-over-mqtt/
		https://arduinojson.org/v6/example/ - Version 6!