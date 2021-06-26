/*
* Project Name: TM1638plus_RPI
* File: TM1638plus.cpp
* Description: source file Raspberry pi  
* library for TM1638 module(LED & KEY). Model 1 & Model 3
* Author: Gavin Lyons.
* Created June 2021
* URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#include "TM1638plus.h"


TM1638plus::TM1638plus(uint8_t strobe, uint8_t clock, uint8_t data) : TM1638plus_common(strobe, clock, data) {
 // Blank constructor
}


void TM1638plus::setLED(uint8_t position, uint8_t value)
{
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_OUTP);
	sendCommand(TM_WRITE_LOC);
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_LEDS_ADR + (position << 1));
	sendData(value);
	bcm2835_gpio_write(_STROBE_IO, HIGH);
}

void TM1638plus::setLEDs(uint16_t ledvalues)
{
	for (uint8_t LEDposition = 0;  LEDposition < 8; LEDposition++) {
		uint8_t colour = 0;

		if ((ledvalues & (1 << LEDposition)) != 0) {
			colour |= TM_RED_LED; //scan lower uint8_t, set Red if one
		} 

		if ((ledvalues & (1 << (LEDposition + 8))) != 0) {
			colour |= TM_GREEN_LED; //scan upper uint8_t, set green if one
		}

		setLED(LEDposition, colour);
	}
}


void TM1638plus::displayIntNum(unsigned long number, bool leadingZeros)
{
	char values[TM_DISPLAY_SIZE + 1];
	snprintf(values, TM_DISPLAY_SIZE + 1, leadingZeros ? "%08ld" : "%ld", number); 
	displayText(values);
}


void TM1638plus::DisplayDecNumNibble(uint16_t  numberUpper, uint16_t numberLower, bool leadingZeros)
{
	char valuesUpper[TM_DISPLAY_SIZE + 1];
	char valuesLower[TM_DISPLAY_SIZE/2 + 1];
	snprintf(valuesUpper, TM_DISPLAY_SIZE/2 + 1, leadingZeros ? "%04d" : "%d", numberUpper);
	snprintf(valuesLower, TM_DISPLAY_SIZE/2 + 1, leadingZeros ? "%04d" : "%d", numberLower); 
	strcat(valuesUpper ,valuesLower);
	displayText(valuesUpper);
}

void TM1638plus::displayText(const char *text) {
	char c, pos;
	pos = 0;
		while ((c = (*text++)) && pos < TM_DISPLAY_SIZE)  {
		if (*text == '.' && c != '.') {
			displayASCIIwDot(pos++, c);

			text++;
		}  else {
			displayASCII(pos++, c);
		}
		}
}


void TM1638plus::displayASCIIwDot(uint8_t position, uint8_t ascii) { 
		// add 128 or 0x080 0b1000000 to turn on decimal point/dot in seven seg
	display7Seg(position, SevenSeg[ascii- TM_ASCII_OFFSET] + TM_DOT_MASK_DEC);
}

void TM1638plus::display7Seg(uint8_t position, uint8_t value) { // call 7-segment
	sendCommand(TM_WRITE_LOC);
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_SEG_ADR + (position << 1));
	sendData(value);
	bcm2835_gpio_write(_STROBE_IO, HIGH); 
}


void TM1638plus::displayASCII(uint8_t position, uint8_t ascii) {
	display7Seg(position, SevenSeg[ascii - TM_ASCII_OFFSET]);
}
 
void TM1638plus::displayHex(uint8_t position, uint8_t hex) 
{
		uint8_t offset = 0;
		if (hex <= 9)
		{
			display7Seg(position, SevenSeg[hex + TM_HEX_OFFSET]);
			// 16 is offset in reduced ASCII table for 0 
		}else if ((hex >= 10) && (hex <=15))
		{
			// Calculate offset in reduced ASCII table for AbCDeF
			switch(hex) 
			{
			 case 10: offset = 'A'; break;
			 case 11: offset = 'b'; break;
			 case 12: offset = 'C'; break;
			 case 13: offset = 'd'; break;
			 case 14: offset = 'E'; break;
			 case 15: offset = 'F'; break;
			}
			display7Seg(position, SevenSeg[offset-TM_ASCII_OFFSET]);
		}
		
}


uint8_t TM1638plus::readButtons()
{
	uint8_t buttons = 0;
	uint8_t v =0;
	
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_BUTTONS_MODE); 
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_INPT);
	for (uint8_t i = 0; i < 4; i++)
	{
		v = HighFreqshiftin(_DATA_IO, _CLOCK_IO) << i;
		buttons |= v;
	}

	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(_STROBE_IO, HIGH);
	return buttons;
}


