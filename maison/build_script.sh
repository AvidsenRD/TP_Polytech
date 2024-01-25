#!/bin/bash
gcc ../mqtt/src/api_mqtt.c ../gpio/src/api_led.c ../gpio/src/api_hall.c ../gpio/src/api_servo.c -l bcm2835 -l paho-mqtt3a -l paho-mqtt3c -o main main.c 
echo "Build finish"
sudo ./main