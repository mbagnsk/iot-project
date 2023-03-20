import paho.mqtt.client as mqtt
import sys
import json

topic = sys.argv[1]


def on_connect(client, userdata, flags, rc):
    print("Connected with result code: " + str(rc))
    client.subscribe(topic)


def on_message(client, userdata, msg):
    try:
        message_received = json.loads(msg.payload)
        print(message_received["message"]["measurement"]["measurementType"])
    except ValueError:
        print("Decoding JSON has failed")


client = mqtt.Client()
client.connect("192.168.1.54", 1884, 60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()
