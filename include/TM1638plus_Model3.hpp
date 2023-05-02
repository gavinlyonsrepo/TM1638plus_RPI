/*!
	@file     TM1638plus_Model3.hpp
	@author   Gavin Lyons
	@brief    RPI library Tm1638plus, Source file for for TM1638 module(LED & KEY). Model 3
	@note  See URL for full details. https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/


#ifndef TM1638PLUSMODEL3_H
#define TM1638PLUSMODEL3_H

#include "TM1638plus_Model1.hpp"

/*!
	@brief Class for Model 3
*/
class TM1638plus_Model3 : public TM1638plus_Model1  {

public:

	/*! Tm1638 bi-color LED colors */
	enum TMLEDColors : uint8_t
	{
		TM_RED_LED = 0x02,  /**< Turn on Red LED*/
		TM_GREEN_LED = 0x01, /**< Turn on Green LED*/
		TM_OFF_LED = 0x00 	/**< Turn off  LED*/
	};
	
	// Constructor 
	TM1638plus_Model3 (uint8_t strobe, uint8_t clock, uint8_t data) ;
	
	// These methods over-ride the super class.
	virtual void setLEDs(uint16_t greenred) override;
	virtual void setLED(uint8_t position, uint8_t value) override;
	
};

#endif
