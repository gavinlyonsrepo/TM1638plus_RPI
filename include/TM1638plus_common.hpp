/*!
	@file     TM1638plus_common.hpp
	@author   Gavin Lyons
	@brief    RPI library Tm1638plus, Header  file for common data and functions between model classes. 
	@note  See URL for full details. https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#ifndef TM1638PLUS_COMMON_H
#define TM1638PLUS_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <bcm2835.h>


/*!
	@brief  The base Class , used to store common data & functions for all models types.
*/
class TM1638plus_common{

public:

	/*! Alignment of text on display */
	enum AlignTextType_e : uint8_t 
	{
		TMAlignTextRight = 1, /**< Align text to the right on  display */
		TMAlignTextLeft = 2, /**< Align text to the left on  display */
		TMAlignTextZeros = 3 /**< Add leading zeros  to the text */
	};

	/*! Display Offsets and Masks*/
	enum TMOffsetsMasks : uint8_t
	{
		TM_ASCII_OFFSET = 0x20, /**< 32 Ascii table offset to jump over first missing 32 chars */
		TM_HEX_OFFSET   = 0x10, /**< 16 Ascii table offset to reach number position */
		TM_DOT_MASK_DEC = 0x80, /**< 128  Mask to  switch on decimal point in seven seg. */
		TM_BRIGHT_MASK = 0x07 /**< Brightness mask */
	};

	/*! Tm1638 register commands*/
	enum TMCommands : uint8_t
	{
		TM_ACTIVATE = 0x8F, /**< Start up */
		TM_BUTTONS_MODE = 0x42, /**< Buttons mode */
		TM_WRITE_LOC = 0x44, /**< Write to a location */
		TM_WRITE_INC = 0x40, /**< Incremental write */
		TM_SEG_ADR = 0xC0,  /**< leftmost segment Address C0 C2 C4 C6 C8 CA CC CE */
		TM_LEDS_ADR = 0xC1,  /**< Leftmost LED address C1 C3 C5 C7 C9 CB CD CF */
		TM_BRIGHT_ADR = 0x88 /**< Brightness address */
	};

	// Constructor
	TM1638plus_common(uint8_t strobe, uint8_t clock, uint8_t data);

	void reset(void);
	void displayBegin(void);
	void brightness(uint8_t brightness);
	uint16_t libraryVersionNumberGet(void);
	uint16_t TMCommDelayGet(void);
	void TMCommDelayset(uint16_t);

protected:
	void sendCommand(uint8_t value);
	void sendData(uint8_t  data);
	uint8_t  HighFreqshiftin(uint8_t dataPin, uint8_t clockPin) ;
	void HighFreqshiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val);
	
	uint8_t _STROBE_IO; /**<  GPIO connected to STB on Tm1638  */
	uint8_t _DATA_IO; /**<  GPIO connected to DIO on Tm1638  */
	uint8_t _CLOCK_IO; /**<  GPIO connected to CLk on Tm1638  */
	const uint8_t _TMDisplaySize = 8; /**< size of display in digts */

	const unsigned char * pFontSevenSegptr = SevenSeg; /**<  Pointer to the seven segment font data table */

private:
	const uint16_t _TMLibVerNum = 210; /**< Library version number 210 = 2.1.0*/
	uint16_t _TMCommDelay = 1; /**<  uS delay used in communications , User adjust */
	const uint8_t _TMDefaultBrightness = 0x02; /**<  can be 0x00 to 0x07 , User adjust */
	
	/*! font , map of ASCII values/table to 7-segment, offset to position 32.  */
	const unsigned char SevenSeg[96] = {
	  0x00, /* (space) */
	  0x86, /* ! */
	  0x22, /* " */
	  0x7E, /* # */
	  0x6D, /* $ */
	  0xD2, /* % */
	  0x46, /* & */
	  0x20, /* ' */
	  0x29, /* ( */
	  0x0B, /* ) */
	  0x21, /* * */
	  0x70, /* + */
	  0x10, /* , */
	  0x40, /* - */
	  0x80, /* . */
	  0x52, /* / */
	  0x3F, /* 0 */
	  0x06, /* 1 */
	  0x5B, /* 2 */
	  0x4F, /* 3 */
	  0x66, /* 4 */
	  0x6D, /* 5 */
	  0x7D, /* 6 */
	  0x07, /* 7 */
	  0x7F, /* 8 */
	  0x6F, /* 9 */
	  0x09, /* : */
	  0x0D, /* ; */
	  0x61, /* < */
	  0x48, /* = */
	  0x43, /* > */
	  0xD3, /* ? */
	  0x5F, /* @ */
	  0x77, /* A */
	  0x7C, /* B */
	  0x39, /* C */
	  0x5E, /* D */
	  0x79, /* E */
	  0x71, /* F */
	  0x3D, /* G */
	  0x76, /* H */
	  0x30, /* I */
	  0x1E, /* J */
	  0x75, /* K */
	  0x38, /* L */
	  0x15, /* M */
	  0x37, /* N */
	  0x3F, /* O */
	  0x73, /* P */
	  0x6B, /* Q */
	  0x33, /* R */
	  0x6D, /* S */
	  0x78, /* T */
	  0x3E, /* U */
	  0x3E, /* V */
	  0x2A, /* W */
	  0x76, /* X */
	  0x6E, /* Y */
	  0x5B, /* Z */
	  0x39, /* [ */
	  0x64, /* \ */
	  0x0F, /* ] */
	  0x23, /* ^ */
	  0x08, /* _ */
	  0x02, /* ` */
	  0x5F, /* a */
	  0x7C, /* b */
	  0x58, /* c */
	  0x5E, /* d */
	  0x7B, /* e */
	  0x71, /* f */
	  0x6F, /* g */
	  0x74, /* h */
	  0x10, /* i */
	  0x0C, /* j */
	  0x75, /* k */
	  0x30, /* l */
	  0x14, /* m */
	  0x54, /* n */
	  0x5C, /* o */
	  0x73, /* p */
	  0x67, /* q */
	  0x50, /* r */
	  0x6D, /* s */
	  0x78, /* t */
	  0x1C, /* u */
	  0x1C, /* v */
	  0x14, /* w */
	  0x76, /* x */
	  0x6E, /* y */
	  0x5B, /* z */
	  0x46, /* { */
	  0x30, /* | */
	  0x70, /* } */
	  0x01, /* ~ */
	};


};

#endif
