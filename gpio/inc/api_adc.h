#ifndef API_ADC_H
#define API_ADC_H
/**
* \file api_adc.h
* \brief header file to handle adc to read analog value
*/
#include <stdint.h>

void init_adc();

uint16_t read_adc(uint8_t channel);

#endif