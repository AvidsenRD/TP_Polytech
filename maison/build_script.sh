#!/bin/bash
gcc ../mqtt/src/api_mqtt.c ../gpio/src/api_led.c ../gpio/src/api_hall.c ../gpio/src/api_servo.c ../gpio/src/api_adc.c ../gpio/src/api_thermostat.c ../gpio/src/api_button.c  -lm -l bcm2835 -l paho-mqtt3a -l paho-mqtt3c -o build/main main.c 
echo "Build finish"
sudo ./build/main