/*
	Project Name: TM1638
	File: main.cpp
	Description: demo file library for  TM1638 module(LED & KEY). Model 1
	Carries out series of tests demonstrating arduino library TM1638plus.
	Author: Gavin Lyons.
	Created June 2021
	URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI
	* 
	* NOTE: in last Test, Test14 buttons test , Press S1 & S8 together to quit
*/

#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <TM1638plus.h>

// GPIO I/O pins on the Arduino connected to strobe, clock, data,
//pick on any I/O you want.
#define  STROBE_TM 23 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 24  // clock = GPIO connected to clock line of module
#define  DIO_TM 25 // data = GPIO connected to data line of module


//Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO)
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM);


// Some vars and defines for the tests.
#define myTestDelay  5000
#define myTestDelay1 1000
uint8_t  testcount = 0;

void Test0(void);  // void Test 0 reset
void Test1(void);  // Brightness
void Test2(void);  // ASCII display
void Test3(void);  // Set a single segment
void Test4(void);  // Hex digits
void Test5(void);  // Text String with Decimal point
void Test6(void);  // TEXT + ASCII combo
void Test7(void);  // Integer Decimal number
void Test8(void);  // Text String + Float hack
void Test9(void);  // Text String + decimal number
void Test10(void);  // Multiple Decimal points
void Test11(void);  // Display Overflow
void Test12(void);  // Scrolling text
void Test13(void);  // setLED and setLEDs
void Test14(void);  // Buttons + LEDS NOTE: Press S1 & S8 together to quit

void doLEDs(uint8_t value);
static uint64_t RPI_Millis( void );

int main(int argc, char **argv) 
{

	printf("Test Begin\r\n");
	if(!bcm2835_init()) {return -1;}
	
	tm.displayBegin();
	bcm2835_delay(myTestDelay1);
	
	Test0();  //Test 0 reset
	Test1();  // Brightness
	Test2();  // ASCII display
	Test3();  // Set a single segment
	Test4();  // Hex digits
	Test5();  // Text String with Decimal point
	Test6();  // TEXT + ASCII combo
	Test7();  // Integer Decimal number
	Test8();  // Text String + Float hack
	Test9();  // Text String + decimal number
	Test10();  // Multiple Decimal points
	Test11();  // Display Overflow
	Test12();  // Scrolling text
	Test13();  // setLED and setLEDs
	Test14();  // Buttons + LEDS NOTE: Press S1 & S8 together to quit
	
	tm.reset();
	bcm2835_close(); // Close the library, deallocating any allocated memory and closing /dev/mem
	printf("Test End\r\n");
	return 0;
}

void Test0()
{
	// Test 0 reset test
	tm.setLED(0, 1);
	bcm2835_delay(myTestDelay);
	tm.reset();
}

void Test1() {
	// Test 1  Brightness and reset
	for (uint8_t brightness = 0; brightness < 8; brightness++)
	{
		tm.brightness(brightness);
		tm.displayText("00000000");
		bcm2835_delay(myTestDelay1);
	}
	tm.reset();
	// restore default brightness
	tm.brightness(0x02);
}

void Test2() {
	//Test 2 ASCII , display 2.341

	tm.displayASCIIwDot(0, '2');
	tm.displayASCII(1, '3');
	tm.displayASCII(2, '4');
	tm.displayASCII(3, '1');
	bcm2835_delay(myTestDelay);
	tm.reset();
}

void Test3() {
	//TEST 3 single segment (pos, (dp)gfedcba)
	//In this case  segment g (middle dash) of digit position 7
	tm.display7Seg(7, 0b01000000); // Displays "       -"
	bcm2835_delay(myTestDelay);
}

void Test4() {
	// Test 4 Hex digits.
	tm.displayHex(0, 1);
	tm.displayHex(1, 2);
	tm.displayHex(2, 3);
	tm.displayHex(3, 4);
	tm.displayHex(4, 5);
	tm.displayHex(5, 6);
	tm.displayHex(6, 7);
	tm.displayHex(7, 8);  
	bcm2835_delay(myTestDelay); // display 12345678

	tm.displayHex(0, 8);
	tm.displayHex(1, 9);
	tm.displayHex(2, 10);
	tm.displayHex(3, 11);
	tm.displayHex(4, 12);
	tm.displayHex(5, 13);
	tm.displayHex(6, 14);
	tm.displayHex(7, 15);
	bcm2835_delay(myTestDelay); // display 89ABCDEF
}

void Test5() {
	// Test 5 TEXT  with dec point
	// abcdefgh with decimal point for c and d
	tm.displayText("abc.d.efgh");
	bcm2835_delay(myTestDelay);
}

void Test6() {
	// Test6  TEXT + ASCII combo
	// ADC=.2.948
	char text1[] = "ADC=.";
	tm.displayText(text1);
	tm.displayASCIIwDot(4, '2');
	tm.displayASCII(5, '9');
	tm.displayASCII(6, '4');
	tm.displayASCII(7, '8');
	bcm2835_delay(myTestDelay);
	tm.reset();
}

void Test7() {
	// TEST 7a Integer
	tm.displayIntNum(45, false); // "45      "
	bcm2835_delay(myTestDelay);
	// TEST 7b Integer
	tm.displayIntNum(99991, true); // "00099991"
	bcm2835_delay(myTestDelay);
	tm.reset();
	// TEST 7b tm.DisplayDecNumNIbble
	tm.DisplayDecNumNibble(1234, 5678, false); // "12345678"
	bcm2835_delay(myTestDelay);
	tm.DisplayDecNumNibble(123, 662, true); // "01230662"
	bcm2835_delay(myTestDelay);
}

void Test8() {
	// TEST 8  TEXT STRING + integer SSSSIIII
	char workStr[11];
	uint16_t  data = 234;
	sprintf(workStr, "ADC=.%04d", data); // "ADC=.0234"
	tm.displayText(workStr);
	bcm2835_delay(myTestDelay);
}

void Test9() {
	// TEST 9 Text String + Float  SSSSFFFF ,  just one possible method.
	float voltage = 12.45;
	char workStr[11];
	sprintf(workStr, "ADC=%f", voltage);
	tm.displayText(workStr); // ADC=12.45
	bcm2835_delay(myTestDelay);
	tm.reset();
}

void Test10()
{
	//TEST 10 Multiple dots test
	tm.displayText("Hello...");
	bcm2835_delay(myTestDelay);
	tm.displayText("...---..."); //SOS in morse
	bcm2835_delay(myTestDelay);
}

void Test11()
{
	//TEST11 user overflow
	tm.displayText("1234567890abc"); //should display just 12345678
	bcm2835_delay(myTestDelay);
	tm.reset();
}


void Test12() {
	//TEST 12 scrolling text, just one possible method.
	char textScroll[17] = " Hello world 123";
	unsigned long previousMillis_display = 0;  // will store last time display was updated
	const long interval_display = 1000;  //   interval at which to update display (milliseconds)

	while(1)
	{
	tm.displayText(textScroll);
	unsigned long currentMillis = RPI_Millis();
	
	if (currentMillis - previousMillis_display >= interval_display)
	{
		previousMillis_display = currentMillis;
		if (strlen(textScroll) > 0)
		{
			memmove(textScroll, textScroll+1, strlen(textScroll));
			tm.displayText("        "); //Clear display or last character will drag across screen
		}else
		{
			return;
		}
	 }
	}
}


void Test13()
{
	//Test 13 LED display
	uint8_t LEDposition = 0;

	// Test 13A Turn on redleds one by one, left to right, with setLED where 0 is L1 and 7 is L8 (L8 RHS of display)
	for (LEDposition = 0; LEDposition < 8; LEDposition++) {
		tm.setLED(LEDposition, 1);
		bcm2835_delay(500);
		tm.setLED(LEDposition, 0);
	}

	// TEST 13b test setLEDs function (0xLEDXX) ( L8-L1 , XX )
	// NOTE passed L8-L1 and on display L8 is on right hand side. i.e. 0x01 turns on L1. LXXX XXXX
	// For model 1 just use upper byte , lower byte is is used by model3 for bi-color leds leave at 0x00 for model 1.
	tm.setLEDs(0xFF00); //  all LEDs on 
	bcm2835_delay(3000);
	 tm.setLEDs(0x0100); // Displays as LXXX XXXX (L1-L8) , NOTE on display L8 is on right hand side.
	bcm2835_delay(3000);
	tm.setLEDs(0xF000); //  Displays as XXXX LLLL (L1-L8) , NOTE on display L8 is on right hand side.
	bcm2835_delay(3000);
	tm.setLEDs(0x0000); // all off
	bcm2835_delay(3000);

}

void Test14() {
	//Test 14 buttons and LED test, press switch number S-X to turn on LED-X, where x is 1-8.
	// NOTE: Press S1 & S8 together to quit
	tm.displayText("buttons ");
	bcm2835_delay(2000);
	while (1) // Loop here forever
	{
		uint8_t buttons = tm.readButtons();
			/* buttons contains a byte with values of button s8s7s6s5s4s3s2s1
			 HEX  :  Switch no : Binary
			 0x01 : S1 Pressed  0000 0001 
			 0x02 : S2 Pressed  0000 0010 
			 0x04 : S3 Pressed  0000 0100 
			 0x08 : S4 Pressed  0000 1000 
			 0x10 : S5 Pressed  0001 0000 
			 0x20 : S6 Pressed  0010 0000 
			 0x40 : S7 Pressed  0100 0000 
			 0x80 : S8 Pressed  1000 0000  
			*/
		doLEDs(buttons);
		tm.displayIntNum(buttons, true); 
		bcm2835_delay(250); 
		if (buttons == 129) break; // if Press S1 & S8 together =  quit loop
	}
}

// scans the individual bits of value sets a LED based on which button pressed
void doLEDs(uint8_t value) {
	for (uint8_t LEDposition = 0; LEDposition < 8; LEDposition++) {
		tm.setLED(LEDposition, value & 1);
		value = value >> 1;
	}
}

//This returns milli-seconds as a 64-bit unsigned number, monotonically increasing, 
//since system boot. 
static uint64_t RPI_Millis( void )
{
  struct timespec now;
  clock_gettime( CLOCK_MONOTONIC, &now );
   return  (uint64_t)now.tv_sec * 1000U + ((uint64_t)now.tv_nsec/1000000U);
}
