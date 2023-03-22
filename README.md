# iot-project

Goal of the project is to comunicate some IoT devices as: ESP8266 and Raspberry PI via MQTT comunication protocol.
Some of ESP8266s would work as sensors that measure weather conditions or other type of data then send that information to MQTT broker that would be installed on Raspberry Pi.
Moreover it's plan to install data base on Raspberry Pi and store there sent data.
Stored data would be used to generate raports or online visualization.

TO DO:
  - visualization,
  - error handling

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
			"idUnit": ...,
			"measurementType": ...,
			"measurementDateTime": ...
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
topic: id_iothub/message_type/action_type/id_device/id_channel
example: 1/measurements/temperature/1/1
```

Subscriber(Raspberry Pi) of the topic gets all information that publicated on specified topic. 

## Raspberry Pi

On Raspberry Pi installed Raspberry Pi OS - linux distribution dedicated for Raspberry devices - and Mosquitto.

Created cfg.conf file in specified for config files location.

```
/etc/mosquitto/conf.d 
```

Cfg.conf contains special options and instructions for broker session.
Defined instructions:

```
allow_anonymous true
listener 1884
```

By default Mosquitto runs automaticlly after Raspberry Pi system start.
It's nessesery to use instructions below to run new broker process with specified configuration:

```
sudo systemctl disable mosquitto.service
sudo systemctl stop mosquitto.service
mosquitto -c /etc/mosquitto/conf.d/cfg.conf -p 1884
``` 

Runs below commend result is device IP in local network.
It may indicate the broker address:

```
hostname -I
```

## SQLite3

Selected a SQLite as a data base engine for project. Data base is installed on Raspberry PI:
Data base name is:

```
measurementsDB
```

and it's stored into:

```
/home/mibagi/measurementsDB.db 
```

Database structure:

![image](https://user-images.githubusercontent.com/56918406/227036589-1f1763f6-6918-4237-9a28-5545b4747f0f.png)


## ESP8266

ESP8266 modul: ESP8266 NodeMcu V3 CH340

Ardiono IDE settings:
  - Board: NodeMCU 1.0 (ESP-12E Module),
  - Upload Speed - 115200,
  - CPU Frequency: 80MHz.

Libraries:
  - String,
  - ArduinoMqttClient,
  - ArduinoJson - https://arduinojson.org/,
  - ESP8266WiFi - http://arduino.esp8266.com/stable/package_esp8266com_index.json - need to be added: FIle -> Preferences -> Additional URL...
  - ESPDateTime.

## Store data

Subscriber program would subscribe topic:

```
+/measurements/temperature/#
```

That allows to get all informations from all devices that publish data on topic that begins: 
```
*/measurements/temperature/*
```
