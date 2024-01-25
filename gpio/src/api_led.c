/**
* \file api_led.c
* \brief handle LED with or without PWM
*/
#include "../inc/api_led.h"
#include <bcm2835.h>
#include <stdio.h>

#define PWM_CHANNEL 0
// This controls the max range of the PWM signal
#define RANGE 100

static uint8_t number_led = 0;
/**
* \fn void init_led_object (led_object * led)
* \brief Initialize a led object
* \param led Pointer to the led object to initialise
*/
void init_led_object(led_object * led)
{
    bcm2835_gpio_fsel(led->pin, BCM2835_GPIO_FSEL_OUTP);
    printf("Creation of LED%d, GPIO : %d, state : %d, pwm : %d\n", led->ID, led->pin, led->state, led->pwm);
}
/**
* \fn set_state_led (led_object * led, int state)
* \brief Change the state of a led object
* \param *led Pointer to the led object to set state
* \param state State to give to the led. If the led is in PWM mode, the given value is the pwm value, if not, the value is 1 : ON, 0 : OFF
*/
void set_state_led(led_object * led, int state)
{
    
    if(state > 1)
        state = 1;
    bcm2835_gpio_write(led->pin, state);

    led->state = state;
    printf("LED%d state : %d\n", led->ID, led->state);
}
/**
* \fn get_state_led (led_object * led)
* \brief Return the state of a led object
* \param *led Pointer to the led object to get the state
* \return State of the led. If the led is in PWM mode, the given value is the pwm value, if not, the value is 1 : ON, 0 : OFF
*/
uint8_t get_state_led(led_object * led)
{
    return led->state;
}

