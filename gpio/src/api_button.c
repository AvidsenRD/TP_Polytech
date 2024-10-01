#include "../inc/api_button.h"
#include <bcm2835.h>

static uint8_t number_button = 0;

/**
* \fn void init_button_object (button_object * led)
* \brief Initialize a button object
* \param button Pointer to the button object to initialise
*/
void init_button_object(button_object *button)
{
    bcm2835_gpio_fsel(button->pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(button->pin, BCM2835_GPIO_PUD_UP);
    button->ID = number_button++;
    read_button(button);
}

/**
* \fn read_button (button_object *button)
* \brief Return the state of a button object
* \param *button Pointer to the button object to read
* \return State of the button.
*/
uint8_t read_button(button_object *button)
{
    button->state = bcm2835_gpio_lev(DATAIN)(button->pin);
    return button->state;
}