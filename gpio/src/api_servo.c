/**
* \file api_servo.c
* \brief handle servo motor
*/
#include "../inc/api_servo.h"
#include <stdio.h>
#include <bcm2835.h>

#define PWM_CHANNEL 1
// This controls the max range of the PWM signal
#define RANGE 50

/**
* \fn init_servo_object (servo_object * servo)
* \brief Initialize a servo object
* \param *servo Pointer to the servo object to initialise
*/
void init_servo_object(servo_object * servo)
{
    printf("Creation of servo, pin :%d\n", servo->pin);
}
/**
* \fn get_position_servo (servo_object * servo)
* \brief Return the position of a servo object
* \param *servo Pointer to the servo object to get the position
* \return Position of the servo object.
*/
uint8_t get_position_servo(servo_object * servo)
{
    return 1;
}
/**
* \fn set_position_servo (servo_object * servo, uint8_t position)
* \brief Set the position of a servo object
* \param *servo Pointer to the servo object to set position
* \param position Position to give to the servo
*/
void set_position_servo(servo_object * servo, uint8_t position)
{
    printf("Position servo set to %d\n", position);
}
