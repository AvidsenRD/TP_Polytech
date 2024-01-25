/**
* \file api_servo.h
* \brief header file to handle servo motor
*/
#ifndef API_SERVO_H
#define API_SERVO_H
#include <stdint.h>

/**
* \struct servo_object api_servo.h
* \brief Structure to handle a servo object
* \param pin Pin where the servo is connected
* \param channel Channel of the PWM
* \param position Position of the servo motor
* \param speed Speed of the motor (not used)
*/
typedef struct
{
	uint8_t pin;
	uint8_t channel;
	uint8_t position;
	uint8_t speed;
}servo_object;

void init_servo_object(servo_object * servo);

uint8_t get_position_servo(servo_object * servo);

void set_position_servo(servo_object * servo, uint8_t postion);

#endif