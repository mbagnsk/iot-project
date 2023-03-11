# Raspberry Pi wifi connection

1. Check available networks: sudo iwlist wlan0 scan.
2. Open configuration file: sudo nano /etc/wpa_supplicant/wpa_supplicant.conf.
3. Configure the file - change county, ssid, psk to the propes ones(is possible to add more than only one network configuration).
4. Reboot device: sudo reboot.
5. Verify connection: ifconfig wlan0.

Source: https://linuxhint.com/connect-raspberry-pi-wifi-using-terminal/
