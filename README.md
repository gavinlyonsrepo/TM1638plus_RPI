![ module pics ](https://github.com/gavinlyonsrepo/TM1638plus/blob/master/extra/images/tm16383.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
  * [Test](#test)
  * [Features](#features)
  * [Model One](#model-one)
  * [Model Two](#model-two)
  * [Model Three](#model-three)
  * [Notes](#notes)
  * [Ports](#ports)

Overview
--------------------------------------------
* Name: TM1638plus_RPI
* Author: Gavin Lyons.

* Description:
A Raspberry pi library to display data on a 8-digit TM1638 seven segment module.
Dynamic install-able system level Raspberry Pi C++ library.
Based on my arduino library called "TM1638plus".
This library supports 3 different models, pictured above from left to right.

1. Model 1, The (8 KEY & 8 LED) variant which has 8 LED's and 8 Push buttons.
2. Model 2, The (QYF 16 KEY) variant which has 16 pushbuttons.
3. Model 3, The (LKM1638) variant which has 8 bi-colour LED's and 8 Push buttons.

* Developed on
	1. Raspberry PI 3 model b,
	2. C++ complier g++ (Raspbian 6.3.0-18)
	3. Raspbian 9.13 stretch OS
	4. bcm2835 Library 1.68 (Dependency: used for GPIO control and delays)


Installation
------------------------------

1. Install the dependency bcm2835 Library if not installed (at time of writing latest version is 1.68.)
	* The bcm2835 library is a dependency and provides delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

2. Download the TM1638plus_RPI library
	* Open a Terminal in a folder where you want to download,build & test library
	* Run following command to download from github.

```sh
curl -sL https://github.com/gavinlyonsrepo/TM1638plus_RPI/archive/1.0.tar.gz | tar xz
```

4. Run "make" to run the makefile in base folder to install library, it will be
    installed to usr/lib and usr/include

```sh
cd TM1638plus_RPI-1.0
sudo make
```

Test
--------------------------------

Wire up your Display.
Next step is to test LED display and the just installed library with an example file.

There are five examples files. The default example file is model 1 "hello world".
To decide which one the makefile(In examples folder) builds simply edit "SRC" variable
at top of the makefile(In examples folder). i.e. SRC=src/HELLOWORLD_Model1
in the "User SRC directory Option Section" at top of file.
Pick an example "SRC" directory path and ONE ONLY.
Comment out the rest.

|  List No | example file name  | Model Num | Desc|
| ------ | ------ |  ------ | ------ |
| 1 | HELLOWORLD_Model1 | 1 & 3 | Hello world |
| 2 | HELLOWORLD_Model2 | 2 | Hello world |
| 3 | TEST_Model1 | 1 | test routines  |
| 4 | TEST_Model2 | 2 | test routines  |
| 5 | TEST_Model3 | 3 | test routines  |

Next enter the examples folder and run the makefile in THAT folder,
This makefile builds the examples file using the just installed library.
and creates a test exe file in "bin".
Be sure to use "sudo" as the bcm2835
requires root permissions by default [ see here for more details on that](http://www.airspayce.com/mikem/bcm2835/)

```sh
cd examples/
make
sudo bin/test
```

Features
----------------------

Connections to RPI:

1. GPIO = STB = Strobe
2. GPIO  = CLK  = Clock
3. GPIO = DIO = Data input / output
4. GND
5. VCC 3.3V (or 5V see Note)

NOTE : If VCC is set to 5V, level shift GPIO to 3.3V or damage could result.

This library supports three variants of the TM1638,
which for purposes of this documentation,
will be named Model 1 ,Model 2 and Model 3.

| Model No | Module Name | LEDS | Push buttons |
| ------ | ------ |  ------ | ------ |
| 1 | TM1638 LED & KEY | 8 red only | 8 |
| 2 | TM1638 KEYS, QYF  | 0 | 16 |
| 3 | TM1638 V1.3 or LKM1638  | 8 bi color,  red and green  | 8 |


Model One
--------------------------------------

TM1638 Module 8 Push buttons 8 LEDS (LED & KEY)

![ module ](https://github.com/gavinlyonsrepo/pic_16F18446_projects/blob/master/images/TM1638.jpg)

![ sch ](https://github.com/gavinlyonsrepo/pic_16F18446_projects/blob/master/images/TM1638_2.jpg)

This variant consist of an 8-digit seven segment display with decimal points,
8 Leds and 8 Push buttons. Two 4 digit 3461AS-1 (.34 inch, 4 digit ,common Cathode,  decimal point, RED) are used in this module giving a total of 8 digits. A TM1638 controller chip drives the unit.
The unit is marked (LED & KEY).

**Model 1 Library Functions**

The commented functions can be found in library header file TM1638plus.h.
The library support ASCII ,text ,Hex and allows for setting individual segments,
and the decimal point of segment.
The test example file contains a set of tests demonstrating library functions.
Press S1 and S8 together to quit test file at last test.
For more information see the commented headers in header file.

1. Print an ASCII character.
2. Print an ASCII character with a dot/decimal point.
3. Print a Hexadecimal digit(0-15).
4. Print a long integer number with or without leading zeros.
5. Print two integer numbers (0-9999) to each nibble with or without leading zeros.
6. Print a text string(dots are replaced and dot is turned on preceding digit),
"abc.def" becomes "abcdef" with c decimal point segment switched on.
7. Read buttons status. User may have to debounce buttons depending on application.
debouncing left out to minimise library size.
See [URL LINK](https://github.com/gavinlyonsrepo/Arduino_Clock_3)
for a practical real world example of using this library,
including a example of debouncing the key presses. It is also possible to read multiple key presses.
8. Reset and init module functions.
9. Adjust brightness of module. Support 8 degree brightness adjustment.
If user wishes to change the default brightness at start-up change,
The DEFAULT_BRIGHTNESS define in header file.
10. Manually set segments to create custom patterns.
11. Switch the 8 LEDS on and off, both a set one LED and set all LEDS methods available.


Model Two
-----------------------------------------

TM1638 Module 16 Push buttons (16 KEY) (QYF).

![ module ](https://github.com/gavinlyonsrepo/TM1638plus/blob/master/extra/images/tm16381.jpg)

![ sch ](https://github.com/gavinlyonsrepo/TM1638plus/blob/master/extra/images/tm16382.jpg)

They consist of an 8-digit seven segment display with decimal points,
and 16 Push buttons.Two 4 digit 3461BS-1 (.34 inch, 4 digit ,common Anode,  decimal point, RED)are used in this module giving a total of 8 digits. A TM1638 controller chip drives the unit.
NB :  If your display shows "56781234" for "12345678" see Notes section. Note A.

**Model 2 Library Functions**

The commented functions can be found in library header file TM1638plus_Model2.h.
The library support Strings,decimal ,Hex ,raw ASCII data, setting individual segments,
and the decimal point. For more detailed information on functions see commented headers in header file(.h). Press S16 in test file to go from test8 to test9 and in test9 to quit.

1. Print a Hexadecimal number with or without leading zeros
2. Print a decimal number with or without leading zeros
3. Manually set segments to create custom patterns.
4. Print two 4 digit decimal number(0-9999) to each nibble with or without leading zeros.
5. Print a text string, dot function supported.
6. Read buttons status. User may want to debounce buttons depending on application.
Two different functions to read buttons.
7. Reset and init module functions.
8. Adjust brightness of module. Support 8 degree brightness adjustment.
If user wishes to change the default brightness at start-up change,
The "DEFAULT_BRIGHTNESS" define in header file.
9. Print raw ASCII data without reference to font file.

Model Three
-----------------------------------------

This module is a variant of Model 1. The differences are the LEDs are bigger and bi-color
both red and green, The seven segment display is larger and extra connectors are added for Daisy chaining.
Two 4 digit KYX-5461AS-7.3 (.54 inch, 4 digit ,common cathode,  decimal point, RED)are used in this module
giving a total of 8 digits.

![ module ](https://github.com/gavinlyonsrepo/TM1638plus/blob/master/extra/images/tm16384.jpg)

**Model 3 Library Functions**

The code is the same as model 1 and there is one unique model 3 example file.
setLED and setLEDs functions behaviour is the only difference in code base between 1 and 3.
SetLED: The difference is when you call the setLED function you pass the following to get LEDs to change colour. For more detailed information on functions see commented headers in header file(.h). Press S1 and S8 together to quit test file at last test.

| Model | setLED Value | result |
|    ----   |    ----   |    ----   |
|    1 & 3  |    0   |    LED off   |
|    3   |    1   |    Led green on  |
|    3   |    2   |    LED red on  |
|    1   |    1   |    LED on   |

SetLEDs: When you pass call the setLEDs function you can pass a word pattern where upper byte is turns LEDs green on and lower byte turns LEDs red on . Model one ignores lower byte, Set to 0x00 always.

1. Model 3 setLEDs(word) = 0xGGRR
3. Model 1 setLEDs(word) = 0xRR00

Notes
--------------------------

1. Swapped data on Display issue on some Model 2 modules
2. TM_Comm_Delay Communications optional delay
3. Driving multiple displays.
4. Detecting multiple buttons pressed together.

*Note A* : Swapped display Issue: Model 2 only

For Some users using the arduino library the nibbles in information display byte
where swapped around. This is because there are different versions of modules on market with different wiring.  See issue #3 on github(arduino library ) called Swapped display :: "12345678" becomes "56781234".
If you test library and you see this issue, in order to fix this when you declare the
Object, set the fourth parameter "swap_nibbles" to True, The default is false.

| PCB Model noted Label | Operation | Object constructor 4th parameter |
| ------ | ------ | ------ |
| QYF-TM1638 | default operation | false |
| QYF-TM1638 -Ver 1.0 | Swapped display Fix |  true  |

*Note B* :   TM_Comm_Delay Communications optional delay

It may be necessary to adjust the define TM_Comm_Delay in the TM1638plus_common.h file
It is Microsecond delay used in communications clocking, it is currently set to 1,
It can be set to 0 or higher. On a different CPU Freq RPI it may be necessary to increase/decrease this.

*Note C* : Driving multiple displays.

It is possible to drive multiple modules. Share the DIO and CLK lines and use a unique
STB line for each device. see issue number 10 at github(arduino library) for example code.

*Note D* : Detecting multiple buttons pressed together.

Model 1 and Model 3 CAN detect multiple buttons pressed.

Model 2 has two different functions:

1. ReadKey16 returns a byte with decimal value 1-16 this function cannot
detect multiple buttons pressed.

2. ReadKey16Two returns a 16 bit integer where each bit corresponds to the 16 switch's.
This function can detect multiple buttons pressed.
However due to the wiring  of the module, see SG-X lines  on schematic,
Pressing Certain combinations of buttons will cause the  data on Seven Segments to
change. So the simultaneous use of multiple key presses and the seven segments display
is problematic and limited. See issue 12 on github(arduino lib)  for more details.


Ports
-------------------

My Original Arduino Library the references in Readme notes section refer here.
[ Link ](https://github.com/gavinlyonsrepo/TM1638plus)

MicroChip PIC XC8 port.
[ Link ](https://github.com/gavinlyonsrepo/pic_16F18446_projects)

Stm32cubeIDE STM32F303k8T6  C++
[Link](https://github.com/gavinlyonsrepo/STM32_projects)
