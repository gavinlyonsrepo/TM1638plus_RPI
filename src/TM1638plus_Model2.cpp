/*
* Project Name: TM1638plus 
* File: TM1638plus_Model2.cpp
* Description: Source cpp file for Rapsberry pi library for "Model 2" TM1638 module(16 KEY 16 pushbuttons).
* Author: Gavin Lyons.
* Created: June 2021
* URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#include "TM1638plus_Model2.h"

TM1638plus_Model2::TM1638plus_Model2(uint8_t strobe, uint8_t clock, uint8_t data,  bool swap_nibbles) : TM1638plus_common(strobe, clock, data) {

	_SWAP_NIBBLES = swap_nibbles;
}

void TM1638plus_Model2::DisplaySegments(uint8_t segment, uint8_t digit)
{
	 if (_SWAP_NIBBLES == true)
	 {
		uint8_t upper , lower = 0;
		lower = (digit) & 0x0F;  // select lower nibble
		upper =  (digit >> 4) & 0X0F; //select upper nibble
		digit = lower << 4 | upper;
	 }

	segment = (segment<<1);
	sendCommand(TM_WRITE_LOC);
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_SEG_ADR | segment);
	sendData(digit);
	bcm2835_gpio_write(_STROBE_IO, HIGH);
}


void TM1638plus_Model2::DisplayHexNum(uint16_t  numberUpper, uint16_t numberLower, uint8_t dots, AlignTextType_e TextAlignment)
{
	char valuesUpper[TM_DISPLAY_SIZE + 1];
	char valuesLower[TM_DISPLAY_SIZE/2 + 1];
	char TextDisplay[5] = "%";
	char TextRight[3] = "4X";
	char TextLeft[4] = "-4X";
	char TextLeadZero[4] = "04X";
	
	switch(TextAlignment) 
	{
		case TMAlignTextRight: strcat(TextDisplay ,TextRight); break; // %4X
		case TMAlignTextLeft: strcat(TextDisplay ,TextLeft); break;  // %-4X
		case TMAlignTextZeros: strcat(TextDisplay ,TextLeadZero); break; // %04X
	}
	
	snprintf(valuesUpper, TM_DISPLAY_SIZE/2 + 1, TextDisplay, numberUpper);
	snprintf(valuesLower, TM_DISPLAY_SIZE/2 + 1, TextDisplay, numberLower); 
	strcat(valuesUpper ,valuesLower);
	DisplayStr(valuesUpper, dots);
	
}

void TM1638plus_Model2::DisplayDecNum(unsigned long number, uint8_t dots, AlignTextType_e TextAlignment)
{
	char values[TM_DISPLAY_SIZE + 1];
	char TextDisplay[6] = "%";
	char TextRight[4] = "8ld";
	char TextLeft[3] = "ld";
	char TextLeadZero[5] = "08ld";
	
	switch(TextAlignment) 
	{
		case TMAlignTextRight: strcat(TextDisplay ,TextRight); break; // %8ld
		case TMAlignTextLeft: strcat(TextDisplay ,TextLeft); break;  // %ld
		case TMAlignTextZeros: strcat(TextDisplay ,TextLeadZero); break; // %08ld
	}
	snprintf(values, TM_DISPLAY_SIZE + 1, TextDisplay, number); 
	DisplayStr(values, dots);
}

void TM1638plus_Model2::DisplayDecNumNibble(uint16_t  numberUpper, uint16_t numberLower, uint8_t dots, AlignTextType_e TextAlignment){
	
	char valuesUpper[TM_DISPLAY_SIZE + 1];
	char valuesLower[TM_DISPLAY_SIZE/2 + 1];
	char TextDisplay[5] = "%";
	char TextRight[3] = "4d";
	char TextLeft[4] = "-4d";
	char TextLeadZero[4] = "04d";
	
	switch(TextAlignment) 
	{
		case TMAlignTextRight: strcat(TextDisplay ,TextRight); break; // %4d
		case TMAlignTextLeft: strcat(TextDisplay ,TextLeft); break;  // %-4d
		case TMAlignTextZeros: strcat(TextDisplay ,TextLeadZero); break; // %04d
	}
	
	snprintf(valuesUpper, TM_DISPLAY_SIZE/2 + 1, TextDisplay, numberUpper);
	snprintf(valuesLower, TM_DISPLAY_SIZE/2 + 1, TextDisplay, numberLower); 
	strcat(valuesUpper ,valuesLower);
	DisplayStr(valuesUpper, dots);
}

void TM1638plus_Model2::DisplayStr(const char* string, uint16_t dots)
{
	uint8_t values[TM_DISPLAY_SIZE];
	bool done = false;
	uint8_t Result  = 0; 
	memset(values, 0, TM_DISPLAY_SIZE * sizeof(uint8_t));

	for (uint8_t  i = 0; i < TM_DISPLAY_SIZE; i++) 
	{
	 if (!done && string[i] != '\0') {
		if (dots >> (7-i) & 1){  //if dots bit is set for that position apply the mask to turn on dot(0x80).
			Result = SevenSeg[string[i] - TM_ASCII_OFFSET];
			values[i] = (Result | TM_DOT_MASK_DEC); //apply the Dot bitmask to value extracted from ASCII table
			}
		else 
			values[i] = SevenSeg[string[i] - TM_ASCII_OFFSET] ;
		}
	else {
		done = true;
		values[i] = (((dots >> (7 - i)) & 1) << 7);
		}

	}
 ASCIItoSegment(values);
}

void TM1638plus_Model2::ASCIItoSegment(const uint8_t values[])
{
	for (uint8_t  segment = 0; segment < TM_DISPLAY_SIZE; segment++) {
	uint8_t  SegmentValue = 0;
	for (uint8_t  j = 0; j < TM_DISPLAY_SIZE; j++) {
		SegmentValue |= ((values[j] >> segment) & 1) << (TM_DISPLAY_SIZE - j - 1);
	}
	DisplaySegments(segment , SegmentValue);
	}
}

unsigned char TM1638plus_Model2::ReadKey16()
{
	unsigned char c[4], i, key_value=0;
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_BUTTONS_MODE);
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_INPT);
	for (i = 0; i < 4; i++)
	{
		
		c[i] =  HighFreqshiftin(_DATA_IO, _CLOCK_IO);
		
		if (c[i] == 0x04) key_value = 1 + (2*i); //00000100 4 0x04
		if (c[i] == 0x40) key_value = 2 + (2*i); //01000000 64 0x40
		if (c[i] == 0x02) key_value = 9 + (2*i); //00000010 2 0x02
		if (c[i] == 0x20) key_value = 10 + (2*i);  //00100000 32 0x20
	}
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(_STROBE_IO, HIGH); 
	return (key_value);
	// Data matrix for read key_value. 
	// c3 0110 0110  c2 0110 0110  c1 0110 0110  c0 0110 0110 :uint8_ts read 
	//    8,16 7,15     6,14 5,13     4,12 3,11     2,10  1,9 :button value
}

 uint16_t TM1638plus_Model2::ReadKey16Two()
{
		
	uint16_t key_value = 0;
	uint8_t Datain ,i = 0;
	bcm2835_gpio_write(_STROBE_IO, LOW);
	sendData(TM_BUTTONS_MODE);
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_INPT);
	for (i = 0; i < 4; i++)
	{
		Datain =  HighFreqshiftin(_DATA_IO, _CLOCK_IO);
		// turn Datain ABCDEFGI = 0BC00FG0  into 00CG00BF see matrix below
		Datain = (((Datain & 0x40) >> 3 | (Datain & 0x04)) >> 2) | (Datain & 0x20) | (Datain & 0x02) << 3;
		 // i = 0 Datain =  00,10,9,0021 // i = 1 Datain  = 00,12,11,0043
		 // i = 2 Datain =  00 ,14,13,0065 // i = 3 Datain =  00,16,15,0087
		 // key_value =  16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1. 
		key_value |= ((Datain & 0x000F) << (2*i)) | (((Datain & 0x00F0) << 4) << (2*i));
	}
	bcm2835_gpio_fsel(_DATA_IO, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(_STROBE_IO, HIGH);
	 
	return (key_value);
	
	//  Data matrix for read key_value. c = datain
	//   c3 0110 0110  c2 0110 0110  c1 0110 0110  c0 0110 0110 :uint8_ts read 
	//    8,16 7,15     6,14 5,13     4,12 3,11                   2,10  1,9 :button value
}
