# Raspberry Pi Mosquitto

Mosquitto installation:
  - sudo apt install mosquitto -y

or

  - wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
  - sudo apt-key add mosquitto-repo.gpg.key
	
Mosquitto configuration file: mosquitto.conf which is located in /etc/mosquitto
  1. cd /etc/mosquitto/
  2. cat mosquitto.conf
	
Mosquitto start: sudo systemctl start mosquitto.service 

Mosquitto stop: sudo systemctl stop mosquitto.service 

Mosquitto restart: sudo systemctl restart mosquitto.service 

Subscribe test topic on localhost: mosquitto_sub -h localhost -t test -d
Publish example message on test topic on localhost: mosquitto_pub -h localhost -t test -m message

Sources:
1. https://stevessmarthomeguide.com/install-mosquitto-raspberry-pi/
2. https://blog-techniczny.pl/2021/01/02/instalacja-i-konfiguracja-mosquitto-na-raspberry-pi/
3. https://www.instructables.com/Installing-MQTT-BrokerMosquitto-on-Raspberry-Pi/
4. https://www.devpower.pl/broker-mosquitto-mqtt-na-raspberry-pi/

