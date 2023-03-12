# iot-project

Goal of the project is to comunicate some IoT devices as: ESP32 and Raspberry PI via MQTT comunication protocol.
Some of ESP32s would work as sensors that measure weather conditions or other type of data then send that information to MQTT broker that would be installed on Raspberry Pi.
Moreover it's plan to install data base on Raspberry Pi and store there sent data.
Stored data would be used to generate raports or online visualization.

TO DO:
  - json structure,
  - topics,
  - publish and subscribe infrastucture,
  - visualization
  - ...

## JSON
Used JSON data format:
```json
{
	"message": {
		"device": {
			"idDevice": ...,
			"idChannel": ...,
			"iotHub": ...
		}
		"measurement": {
			"value": ...,
			"measurementType": ...,
			"datetime": ...
		}
	}
}
```

JSON data format used when errors occured:
```json
{
	"fault": {
		"device": {
			"idDevice": ...,
			"idChannel": ...,
			"iotHub": ...
		}
		"error": {
			"code": ...,
			"value": ...,
			"datetime": ...
		}
	}
}
```