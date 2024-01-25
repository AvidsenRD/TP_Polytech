/**
* \file api_hall.c
* \brief handle hall and luminosity sensors
*/
#include "../inc/api_hall.h"
#include <bcm2835.h>
#include <stdio.h>

static uint8_t number_hall = 0;

/**
* \fn init_hall_object (hall_object * hall)
* \brief Initialize a hall object
* \param *hall Pointer to the hall object to initialise
*/
void init_hall_object(hall_object * hall)
{
    printf("Creation of HALL%d, pin :%d, state : %d\n", hall->ID, hall->pin, hall->state);
}
/**
* \fn get_state_hall (hall_object * hall)
* \brief Return the state of a hall object
* \param *hall Pointer to the hall object to get the state
* \return State of the hall object.
*/
uint8_t get_state_hall(hall_object * hall)
{
    printf("HALL%d state = %d, old state = %d\n", hall->ID, hall->state, hall->old_state);
    return 1;
}
/**
* \fn get_old_state_hall (hall_object * hall)
* \brief Return the previous state of a hall object
* \param *hall Pointer to the hall object to get the state
* \return Previous state of the hall object.
*/
uint8_t get_old_state_hall(hall_object * hall)
{
	return 1;
}