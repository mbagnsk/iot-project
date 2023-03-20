import paho.mqtt.client as mqtt
import sys
import json
from measurements_database_handler import add_temperature_measurement

topic = sys.argv[1]

measurement_type_dictionary = {
    "temperature": "1"
}


def on_connect(client, userdata, flags, rc):
    print("Connected with result code: " + str(rc))
    client.subscribe(topic)


def on_message(client, userdata, msg):
    try:
        message_received = json.loads(msg.payload)
        if message_received["message"]["measurement"]["measurementType"] == measurement_type_dictionary["temperature"]:
            add_temperature_measurement(message_received)
    except ValueError:
        print("Decoding JSON has failed")


client = mqtt.Client()
client.connect("192.168.1.54", 1884, 60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()
