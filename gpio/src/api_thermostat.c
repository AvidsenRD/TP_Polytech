/**
* \file api_thermostat.c
* \brief handle thermostat to measure temperature
*/
#include "../inc/api_thermostat.h"
#include "../inc/api_adc.h"
#include <bcm2835.h>
#include <stdio.h>
#include <math.h>

#define SENSIVITY 1
static uint8_t number_thermostat = 0;

/**
* \fn init_thermostat (thermostat_object *thermostat)
* \brief Initialize thermostat
* \param *thermostat Pointer to the thermostat object to initialise
*/
void init_thermostat(thermostat_object *thermostat)
{
	bcm2835_gpio_fsel(thermostat->relay_pin, BCM2835_GPIO_FSEL_OUTP);
	set_heating_state(thermostat, LOW);

    init_adc();
    thermostat->ID = number_thermostat++;
    printf("Creation of Thermostat%d, channel :%d, relay_pin : %d\n", thermostat->ID, thermostat->adc_channel, thermostat->relay_pin);
}

/**
* \fn read_temperature (thermostat_object *thermostat)
* \brief Return the temperature measured and update old_value
* \param *thermostat Pointer to the thermostat object to get the temperature
* \return Temperature measured
*/
float read_temperature(thermostat_object *thermostat)
{
    float value = read_adc(thermostat->adc_channel);//read value

    thermostat->old_temperature = value;
    //printf("Value = %.1f°c\n", value);
    thermostat->temperature = value;
    return value;
}

/**
* \fn get_old_temperature (thermostat_object *thermostat)
* \brief Return the old temperature measured and update old_value
* \param *thermostat Pointer to the thermostat object to get the old temperature
* \return Old emperature measured
*/
float get_old_temperature(thermostat_object *thermostat)
{
    return thermostat->old_temperature;
}

/**
* \fn is_value_temperature_updated (thermostat_object *thermostat)
* \brief Return the flag of the updated status of the temperature
* \param *thermostat Pointer to the thermostat object to get the status of the temperature
* \return Flag of the updated status
*/
uint8_t is_value_temperature_updated(thermostat_object *thermostat)
{
    return thermostat->updated_value;
}

/**
* \fn set_setpoint (thermostat_object *thermostat, float setpoint)
* \brief Set the set point for the temperature regulation
* \param *thermostat Pointer to the thermostat object to set the setpoint
* \param setpoint Target temperature value
*/
void set_setpoint(thermostat_object *thermostat, float setpoint)
{
    thermostat->setpoint = setpoint;
    printf("Setpoint of Thermostat%d is set to %.1f\n", thermostat->ID, thermostat->setpoint);
}

/**
* \fn get_setpoint (thermostat_object *thermostat)
* \brief Return the target temperature for the regulation
* \param *thermostat Pointer to the thermostat object to get the status of the temperature
* \return Return the setpoint
*/
float get_setpoint(thermostat_object *thermostat)
{
    //printf("Setpoint is %.1f\n", thermostat->setpoint);
    return thermostat->setpoint;
}

/**
* \fn set_heating_state (thermostat_object *thermostat, uint8_t state)
* \brief Handle the relay to regulate temperature
* \param *thermostat Pointer to the thermostat object to set the status of the temperature regulation
* \param state State of the relay
*/
void set_heating_state(thermostat_object *thermostat, uint8_t state)
{
    printf("Thermostat%d heating state = %d\n", thermostat->ID, thermostat->heating_state);
    thermostat->heating_state = state;
	bcm2835_gpio_write(thermostat->relay_pin, state);
}

/**
* \fn get_heating_state (thermostat_object *thermostat)
* \brief Return heating state of the temperature regulation
* \param *thermostat Pointer to the thermostat object to set the status of the temperature regulation
* \return Return the heating state
*/
uint8_t get_heating_state(thermostat_object *thermostat)
{
    return thermostat->heating_state;
}

/**
* \fn on_off_regulation (thermostat_object *thermostat)
* \brief Handle the regulation of temperature with an on off algorithme
* \param *thermostat Pointer to the thermostat object to handle regulation
*/
void on_off_regulation(thermostat_object *thermostat)
{
    if(get_setpoint(thermostat) >= read_temperature(thermostat))
    {
        set_heating_state(thermostat, 0);
    }
    else
    {
        set_heating_state(thermostat, 1);
    }
}

/**
* \fn temperature_to_mqtt (thermostat_object *thermostat, char *message)
* \brief Convert the temperature to an interpretable message for the MQTT server
* \param *thermostat Pointer to the thermostat object to convert the temperature
* \param *message message to store the converted value
*/
void temperature_to_mqtt(thermostat_object *thermostat, char *message)
{
    int temperature = (int)get_old_temperature(thermostat)*10;
    message[0] = temperature%255;
    message[1] = temperature/255;
}