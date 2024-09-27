/**
* \file api_adc.c
* \brief handle adc to read analog value
*/
#include "../inc/api_adc.h"
#include <bcm2835.h>
#include <stdio.h>

static const uint8_t SELPIN     = RPI_GPIO_P1_22;
static const uint8_t DATAOUT    = RPI_GPIO_P1_19;
static const uint8_t DATAIN     = RPI_GPIO_P1_21;
static const uint8_t SPICLOCK   = RPI_GPIO_P1_23;

/**
* \fn init_adc(uint8_t sel, uint8_t out, uint8_t in, uint8_t clock)
* \brief Initialize the ADC (MCP3208)
* \param sel pin select number
* \param out output pin number
* \param in  input pin number
* \param clock clock pin number
*/
void init_adc()
{
	bcm2835_gpio_fsel(SELPIN, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DATAOUT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(SPICLOCK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DATAIN, BCM2835_GPIO_FSEL_INPT);
	//disable device to start with 
	bcm2835_gpio_write(SELPIN, HIGH);
	bcm2835_gpio_write(DATAOUT, LOW);
	bcm2835_gpio_write(SPICLOCK, LOW);

	printf("Init ADC\n");
}

/**
* \fn read_adc(uint8_t channel)
* \brief Read the value of the ADC on the selected channel
* \param channel channel to read the value
* \return The read value
*/
uint16_t read_adc(uint8_t channel)
{
	uint16_t adcvalue = 0;
	uint8_t commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3)
	//allow channel selection
	commandbits|=((channel-1)<<3);

	bcm2835_gpio_write(SELPIN,LOW); //Select adc
	// setup bits to be written
	for (int i=7; i>=3; i--){
		bcm2835_gpio_write(DATAOUT,commandbits&1<<i);
		//cycle clock
		bcm2835_gpio_write(SPICLOCK,HIGH);
		bcm2835_gpio_write(SPICLOCK,LOW);    
	}

	bcm2835_gpio_write(SPICLOCK,HIGH);    //ignores 2 null bits
	bcm2835_gpio_write(SPICLOCK,LOW);
	bcm2835_gpio_write(SPICLOCK,HIGH);  
	bcm2835_gpio_write(SPICLOCK,LOW);

	//read bits from adc
	for (int i=11; i>=0; i--){
		adcvalue+=bcm2835_gpio_lev(DATAIN)<<i;
		//cycle clock
		bcm2835_gpio_write(SPICLOCK,HIGH);
		bcm2835_gpio_write(SPICLOCK,LOW);
	}
	bcm2835_gpio_write(SELPIN, HIGH); //turn off device
	
	return adcvalue;
}