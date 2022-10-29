/*
* Project Name: TM1638plus_RPI 
* File: TM1638plus_common.h
* Description: header  file for common data and functions between model 1 and 2 classes
* Raspberry pi C++ library TM1638plus
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#ifndef TM1638PLUS_COMMON_H
#define TM1638PLUS_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <bcm2835.h>

#define TM_ACTIVATE 0x8F // Start up
#define TM_BUTTONS_MODE 0x42 // Buttons mode
#define TM_WRITE_LOC 0x44 // Write to a location
#define TM_WRITE_INC 0x40 // Incremental write
#define TM_SEG_ADR 0xC0  // leftmost segment Address C0 C2 C4 C6 C8 CA CC CE
#define TM_LEDS_ADR 0xC1  // Leftmost LED address C1 C3 C5 C7 C9 CB CD CF
#define TM_BRIGHT_ADR 0x88 // Brightness address
#define TM_BRIGHT_MASK 0x07 // Brightness mask 
#define TM_DEFAULT_BRIGHTNESS 0x02 //can be 0x00 to 0x07 , User adjust
#define TM_DISPLAY_SIZE 8 //size of display

#define TM_ASCII_OFFSET 32 // Ascii table offset to jump over first missing 32 chars
#define TM_HEX_OFFSET   16 // Ascii table offset to reach number position
#define TM_DOT_MASK_DEC    128 // 0x80 Mask to  switch on decimal point in seven seg.   

#define TM_RED_LED 0x02 // Model 3
#define TM_GREEN_LED 0x01 // Model 3
#define TM_OFF_LED 0x00

#define TM_Comm_Delay 1 // uS delay used in communications , User adjust 

typedef enum 
{
	TMAlignTextRight = 1, 
	TMAlignTextLeft = 2,  
	TMAlignTextZeros = 3 // leading zeros
}AlignTextType_e; // Alignment of text

// font , map of ASCII values/table to 7-segment, offset to position 32. 
const unsigned char SevenSeg[] = {
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

// Class for some common functions 
class TM1638plus_common{

public:
	// Constructor 
	TM1638plus_common(uint8_t strobe, uint8_t clock, uint8_t data);
	
	void reset(void);  // Reset // Clear module 
	
	void displayBegin();	 // Begin method , sets pinmodes , Call in setup
	
	//Sets the brightness level on a scale of brightness = 0 to 7.
	//0 is not turned off, it's just the lowest brightness.
	//If user wishes to change the default brightness at start-up change.
	 //The DEFAULT_BRIGHTNESS define in header file.
	void brightness(uint8_t brightness);
	
	//  Shifts in a data byte on datapin and returns it as a byte 
	// uses TM_Comm_Delay 
	uint8_t  HighFreqshiftin(uint8_t dataPin, uint8_t clockPin) ;
	
	//  Shifts out a data byte (val)  
	//  uses TM_Comm_Delay
	void HighFreqshiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val);
	
protected:
	uint8_t _STROBE_IO;
	uint8_t _DATA_IO;
	uint8_t _CLOCK_IO;
	void sendCommand(uint8_t value);
	void sendData(uint8_t  data);
};

#endif
