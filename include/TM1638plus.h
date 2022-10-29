/*
* Project Name: TM1638plus_RPI
* File: TM1638plus.h
* Description: TM1638plus.h header file Raspberry pi C++ library 
* for TM1638 module(LED & KEY). Model 1 & Model 3
* Author: Gavin Lyons.
* Created June 2021
* URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/


#ifndef TM1638PLUS_H
#define TM1638PLUS_H

#include "TM1638plus_common.h"

class TM1638plus : public TM1638plus_common  {

public:
	// Constructor 
	//Parameters 
	// 1. strobe = GPIO STB pin
	// 2. clock = GPIO CLK  pin
	// 3. data = GPIO DIO pin
	TM1638plus(uint8_t strobe, uint8_t clock, uint8_t data) ;
	
	// Methods
	
	//Read buttons returns a uint8_t with value of buttons 1-8 b7b6b5b4b3b2b1b0
	// 1 pressed, zero not pressed. 
	//User may have to debounce buttons depending on application.
	//See [URL LINK](https://github.com/gavinlyonsrepo/Arduino_Clock_3) 
	// for de-bonce example.
	uint8_t readButtons(void);

	// Send Text to Seven segments, passed char array pointer
	// dots are removed from string and dot on preceding digit switched on
	// "abc.def" will be shown as "abcdef" with c decimal point turned on.
	void displayText(const char *text);

	// Send ASCII value to seven segment, pass position 0-7 and ASCII value uint8_t
	void displayASCII(uint8_t position, uint8_t ascii);

	// Same as displayASCII function but turns on dot/decimal point  as well 
	void displayASCIIwDot(uint8_t position, uint8_t ascii) ;

	// Send HEX value to seven segment, pass position 0-7 and hex value(DEC) 0-15
	void displayHex(uint8_t position, uint8_t hex);

	// Send seven segment value to seven segment
	//  pass position 0-7 uint8_t of data corresponding to segments (dp)gfedcba
	// i.e 0b01000001 will set g and a on. 
	void display7Seg(uint8_t position, uint8_t value);
	
	// Display an integer and leading zeros optional
	// Param 1 :: integer to display 2^32 
	// Param 2 :: enum text alignment , left or right alignment or leading zeros
	void displayIntNum(unsigned long number, AlignTextType_e = TMAlignTextLeft);
	
	// Divides the display into two nibbles and displays a Decimal number in each.
	// takes in two numbers 0-9999 for each nibble ,
	// and leading zeros optional
	// Param 1 :: upper nibble integer 2^16 0-9999
	// Param 2 :: lower nibble integer 2^16 0-9999
	// Param 3 :: enum text alignment , left or right alignment or leading zeros
	void DisplayDecNumNibble(uint16_t numberUpper, uint16_t numberLower,AlignTextType_e = TMAlignTextLeft);
	
	// Set the LEDs. passed one  16bit integer.
	// MODEL 3:
	//MSB uint8_t for the green LEDs, LS uint8_t for the red LEDs (0xgreenred) 
	//ie. 0xE007   1110 0000 0000 0111   results in L8-L0  GGGX XRRR, NOTE L8 is RHS on display
	// MODEL 1:
	// MSB uint8_t 1 for  red LED , LSB uint8_t n/a set to 0x00 (0xleds, 0xXX)
	//i.e 0xF100  1111 0000 L8-L0 RRRRXXX0 NOTE  L8 is RHS on display
	void setLEDs(uint16_t greenred);
	
	// Set an LED, pass it LED position 0-7 and value 0 or 1 , L1-L8
	void setLED(uint8_t position, uint8_t value);
	
};

#endif
