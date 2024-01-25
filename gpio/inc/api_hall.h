/**
* \file api_hall.h
* \brief header file to handle hall and luminosity sensors
*/
#ifndef API_HALL_H
#define API_HALL_H
#include <stdint.h>

/**
* \struct hall_object api_hall.h
* \brief Structure to handle a hall object
* \param pin Pin where the sensor is connected
* \param state State of the sensor
* \param old_state Previous state of the sensor
* \param ID ID of the sensor
*/
typedef struct
{
	uint8_t pin;
	uint8_t state;
	uint8_t old_state;
	int ID;
}hall_object;

void init_hall_object(hall_object * hall);

uint8_t get_state_hall(hall_object * hall);

uint8_t get_old_state_hall(hall_object * hall);

#endif