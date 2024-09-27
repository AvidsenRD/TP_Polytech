/**
* \file main.c
* \brief Main file to handle the whole connected home
*/

/** \mainpage Project connected home for polytech students
* \section intro_sec Structure of the project
* The project is divided in few api to handle different elements of the home :
* * MQTT connection :                     api_mqtt.c
* * LED handling :                        api_led.c
* * Hall and luminosity sensor handling : api_hall.c
* * Servo motor handling :                api_servo.c
* * Thermostat handling :                 api_thermostat.c
* * ADC handling :                        api_adc.c
*/
#include <stdio.h>
#include <bcm2835.h>
#include "../gpio/inc/api_led.h"
#include "../gpio/inc/api_hall.h"
#include "../gpio/inc/api_servo.h"
#include "../gpio/inc/api_thermostat.h"
#include "../mqtt/inc/api_mqtt.h"

led_object LedExtGauche = {RPI_V2_GPIO_P1_11, 0, 0, 0};


extern Object light;

int main(int argc, char* argv[])
{
    printf("Demarrage\n");
    if (!bcm2835_init())
      return 1;

    MQTTClient client1;

//LED Ext
    light.client = client1;
    
    light.obj1 = &LedExtGauche;
    init_led_object(light.obj1);


    connectObject(&light);

    while(1)
    {
    
    }
    return 0;
}
