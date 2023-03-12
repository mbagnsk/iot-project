# ESP32 JSON

It's possible to store data using JSON format on ESP32.
ArduinoJson.h library enables to use JSON objects.

Example:

1. Creating JSOBObject
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
