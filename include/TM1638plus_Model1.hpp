/*!
	@file     TM1638plus_Model1.hpp
	@author   Gavin Lyons
	@brief    RPI library Tm1638plus, Header file for for TM1638 module(LED & KEY). Model 1
	@note  See URL for full details. https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#ifndef TM1638PLUSMODEL1_H
#define TM1638PLUSMODEL1_H

#include "TM1638plus_common.hpp"

/*!
	@brief Class for Model 1
*/
class TM1638plus_Model1 : public TM1638plus_common  {

public:

	TM1638plus_Model1 (uint8_t strobe, uint8_t clock, uint8_t data) ;
	
	uint8_t readButtons(void);
	
	void displayText(const char *text);
	void displayASCII(uint8_t position, uint8_t ascii);
	void displayASCIIwDot(uint8_t position, uint8_t ascii) ;
	void displayHex(uint8_t position, uint8_t hex);
	void display7Seg(uint8_t position, uint8_t value);
	void displayIntNum(unsigned long number, AlignTextType_e = TMAlignTextLeft);
	void DisplayDecNumNibble(uint16_t numberUpper, uint16_t numberLower,AlignTextType_e = TMAlignTextLeft);
	
	// LED methods defined as overridden in sub-class for Model 3
	virtual void setLEDs(uint16_t leds); 
	virtual void setLED(uint8_t position, uint8_t value); 
	
};

#endif
