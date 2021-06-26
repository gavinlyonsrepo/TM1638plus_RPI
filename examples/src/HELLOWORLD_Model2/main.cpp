/*
  Project Name: TM1638plus_RPI 
  File: main.cpp
  Description: A Basic test file for model 2, TM1638 module(16 KEY 16 pushbuttons).
  Author: Gavin Lyons.
  Created June 20221
  URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#include <TM1638plus_Model2.h>
#include <bcm2835.h>
#include <stdio.h>

// GPIO I/O pins on the Arduino connected to strobe, clock, data, pick on any I/O pin you want.
#define  STROBE_TM 23 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 24  // clock = GPIO connected to clock line of module
#define  DIO_TM 25 // data = GPIO connected to data line of module
bool swap_nibbles = false; //Default is false if left out, see issues section in readme at URL

// Constructor object Init the module
TM1638plus_Model2 tm(STROBE_TM, CLOCK_TM , DIO_TM, swap_nibbles);


int main(int argc, char **argv) 
{
	printf("Test Begin\r\n");
	if(!bcm2835_init()) {return -1;}
	
	tm.displayBegin();
	tm.DisplayStr("helowrld", 0);  // Display "helowrld" in 7 segments with 0 decimal points set.
	delay(5000);
	
	tm.reset();
	bcm2835_close(); // Close the library
	printf("Test End\r\n");
	return 0;
}


