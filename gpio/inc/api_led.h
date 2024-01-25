/**
* \file api_led.h
* \brief header file to handle LED with or without PWM
*/
#ifndef API_LED_H
#define API_LED_H
#include <stdint.h>

/**
* \struct led_object api_led.h
* \brief Structure to handle a led object
* \param pin Pin where the led is connected
* \param state State of the led
* \param ID ID of the led
*/
typedef struct
{
	uint8_t pin;
	uint8_t state;
	uint8_t pwm;
	int ID;
}led_object;

void init_led_object(led_object * led);

void set_state_led(led_object * led, int state);

uint8_t get_state_led(led_object * led);

#endif