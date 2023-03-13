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
			"idMeasurement": ...,
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
topic: message_type/acction_type/id_device/id_channel
example: measurements/temperature/1/1
```

* topic for errors
Subscriber(Raspberry Pi) of the topic gets all information that publicated. 

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