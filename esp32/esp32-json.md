# ESP32 JSON

It's possible to store data using JSON format on ESP32.
ArduinoJson.h library enables to use JSON objects.

Example:

1. Creating JSONObject
```c
StaticJsonBuffer<300> JSONbuffer;
JsonObject& JSONencoder = JSONbuffer.createObject();
```

2. Put some keys and values:
```c 
JSONencoder["device"] = "ESP32";
JSONencoder["sensorType"] = "Temperature";
JsonArray& values = JSONencoder.createNestedArray("values");
 
values.add(20);
values.add(21);
values.add(23);
```

3. Result:
```
{
"device": "ESP32",
"sensorType" : "Temperature",
"Value" : [20,21,23]
}
```
 
4. Then it's possible to parse JSON object to string that would can be send via MQTT:
```c
char JSONmessageBuffer[100];
JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
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