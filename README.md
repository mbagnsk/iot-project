# iot-project

Goal of the project is to comunicate some IoT devices as: ESP8266 and Raspberry PI via MQTT comunication protocol.
Some of ESP8266s would work as sensors that measure weather conditions or other type of data then send that information to MQTT broker that would be installed on Raspberry Pi.
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
			"idIoTHub": ...
		}
		"measurement": {
			"value": ...,
			"measurementType": ...,
			"dateTime": ...
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
			"idIoTHub": ...
		}
		"error": {
			"code": ...,
			"value": ...,
			"dateTime": ...
		}
	}
}
```

## MQTT

MQTT is a standards-based messaging protocol, or set of rules, used for machine-to-machine communication.
It allows to comunicate IoT devices effiiently in easy way.

In this project MQTT broker would be installed on Raspberry Pi. MQTT broker is responsible for:
  - autorizing and authenticating MQTT clients,
  - passing messages to other systems for further analysis,
  - handling missed messages and client sessions.

It would be great to restrict access to the broker. It should be enable only for defined devices.
Default port for MQTT Broker is 1883. 

IoT devices connected to the broker would publish data in defined JSON format.
Every message should be assigned to proper topic that defines some informations about publisher.
Example topic body:

```
topic: message_type/action_type/id_device/id_channel
example: measurements/temperature/1/1
```

* topic for errors
Subscriber(Raspberry Pi) of the topic gets all information that publicated. 

## ESP8266

ESP8266 modul: ESP8266 NodeMcu V3 CH340

Ardiono IDE settings:
  - Board: NodeMCU 1.0 (ESP-12E Module),
  - Upload Speed - 115200,
  - CPU Frequency: 80MHz.

Libraries:
  - String,
  - PubSubClient - https://github.com/Imroy/pubsubclient,
  - ArduinoJson - https://arduinojson.org/,
  - ESP8266WiFi - http://arduino.esp8266.com/stable/package_esp8266com_index.json - need to be added: FIle -> Preferences -> Additional URL...
  - ESPDateTime.

## Store data

Subscriber program would subscribe topic:

```
measurements/temperature/#
```

That allows to get all informations from all devices that publish data on topic that begins: 
```
measurements/temperature/*
```
* topic for errors