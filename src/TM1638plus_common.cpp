/*
* Project Name: TM1638plus_RPI
* File: TM1638plus_common
* Description: cpp  file for common data and functions between model 1 and 2 classes
* Raspberry pi library T
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#include "TM1638plus_common.h"


TM1638plus_common::TM1638plus_common(uint8_t strobe, uint8_t clock, uint8_t data)
{
	_STROBE_IO = strobe;
	_DATA_IO = data;
	_CLOCK_IO = clock;
}

void TM1638plus_common::reset() {
	sendCommand(TM_WRITE_INC); // set auto increment mode
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_SEG_ADR);   // set starting address to 0
	for (uint8_t position = 0; position < 16; position++)
	{
		sendData(0x00); //clear all segments
	}
	bcm2835_gpio_write(_STROBE_IO, HIGH);
}

void TM1638plus_common::brightness(uint8_t brightness)
{
	uint8_t  value = 0;
	value = TM_BRIGHT_ADR + (TM_BRIGHT_MASK & brightness);
	sendCommand(value);
}

void TM1638plus_common::displayBegin(void)
{
	bcm2835_gpio_fsel( _STROBE_IO, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(_CLOCK_IO, BCM2835_GPIO_FSEL_OUTP);
	sendCommand(TM_ACTIVATE);
	brightness(TM_DEFAULT_BRIGHTNESS);
	reset();
}

void TM1638plus_common::sendCommand(uint8_t value)
{
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(value);
	bcm2835_gpio_write(_STROBE_IO, HIGH);
}

void TM1638plus_common::sendData(uint8_t data)
{
	HighFreqshiftOut(_DATA_IO, _CLOCK_IO, data);
}


uint8_t  TM1638plus_common::HighFreqshiftin(uint8_t dataPin, uint8_t clockPin) 
{
	uint8_t value = 0;
	uint8_t i = 0;

	for(i = 0; i < 8; ++i) 
	{
		value |= bcm2835_gpio_lev(dataPin) << i;
		bcm2835_gpio_write(clockPin, HIGH);
		bcm2835_delayMicroseconds(TM_Comm_Delay);
		bcm2835_gpio_write(clockPin, LOW);
		bcm2835_delayMicroseconds(TM_Comm_Delay);
	}
	return value;
}

void TM1638plus_common::HighFreqshiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  
	{
		bcm2835_gpio_write(dataPin, !!(val & (1 << i)));
		bcm2835_gpio_write(clockPin, HIGH);
		bcm2835_delayMicroseconds(TM_Comm_Delay);
		bcm2835_gpio_write (clockPin, LOW);
		bcm2835_delayMicroseconds(TM_Comm_Delay);
	}
}
