#ifndef API_BUTTON_H
#define API_BUTTON_H
/**
* \file api_button.h
* \brief header file to handle buttons
*/
#include <stdint.h>

/**
* \struct button_object api_button.h
* \brief Structure to handle a button object
* \param pin Pin where the button is connected
* \param state State of the button
* \param ID ID of the button
*/
typedef struct
{
	uint8_t pin;
	uint8_t state;
	int ID;
}button_object;

void init_button_object(button_object *button);

uint8_t read_button(button_object *button);

#endif