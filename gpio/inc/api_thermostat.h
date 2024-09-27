#ifndef API_THERMOSTAT_H
#define API_THERMOSTAT_H
/**
* \file api_thermostat.h
* \brief header file to handle a thermostat
*/
#include <stdint.h>

/**
* \struct thermostat_object api_hall.h
* \brief Structure to handle a thermostat
* \param adc_channel Channel on the adc where it is connected
* \param relay_pin   Pin of the relay
* \param temperature Temperature measured
* \param old_temperature Old measured temperature
* \param updated_value Flag to see if the old temperature has been updated
* \param setpoint Target temperature
* \param heating_state State of the relay plugged to the resistor
* \param ID ID of the sensor
*/
typedef struct
{
	uint8_t adc_channel;
    uint8_t relay_pin;
	float temperature;
	float old_temperature;
	uint8_t updated_value;
	float setpoint;
    uint8_t heating_state;
	int ID;
}thermostat_object;

void init_thermostat(thermostat_object *themrostat);

float read_temperature(thermostat_object *thermostat);

float get_old_temperature(thermostat_object *thermostat);

uint8_t is_value_temperature_updated(thermostat_object *thermostat);

void set_setpoint(thermostat_object *thermostat, float setpoint);

float get_setpoint(thermostat_object *thermostat);

void set_heating_state(thermostat_object *thermostat, uint8_t state);

uint8_t get_heating_state(thermostat_object *thermostat);

void on_off_regulation(thermostat_object *thermostat);

void temperature_to_mqtt(thermostat_object *thermostat, char *message);

#endif