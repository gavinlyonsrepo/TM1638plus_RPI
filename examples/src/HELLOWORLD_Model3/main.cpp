/*!
	@file TM1638plus_RPI/examples/src/HELLOWORLD_Model3/main.cpp
	@author Gavin Lyons
	@brief A demo file library for TM1638 module Works on Model 3
	Carries out series most basic test , "hello world" helo wrld
	Project Name: TM1638plus_RPI
	URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
*/

#include <TM1638plus_Model3.hpp> //include the library
#include <bcm2835.h>
#include <stdio.h>

// GPIO I/O pins on the raspberry pi connected to strobe, clock, data,
//pick on any I/O you want.
#define  STROBE_TM 23 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 24  // clock = GPIO connected to clock line of module
#define  DIO_TM 25 // data = GPIO connected to data line of module
 
// Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO, )
TM1638plus_Model3 tm(STROBE_TM, CLOCK_TM , DIO_TM);


int main(int argc, char **argv) 
{
	printf("Test Begin\r\n");
	if(!bcm2835_init()) {return -1;}
	
	tm.displayBegin(); 
	tm.displayText("helowrld");
	bcm2835_delay(5000);
	
	tm.reset();
	bcm2835_close(); // Close the library
	printf("Test End\r\n");
	return 0;
}
