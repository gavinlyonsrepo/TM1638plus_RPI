# TM1638plus RPI

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
  * [Test](#test)
  * [Hardware](#hardware)
  * [Notes](#notes)
  * [See Also](#see-also)

Overview
--------------------------------------------
* Name: TM1638plus_RPI
* Author: Gavin Lyons.

* Description:

A Raspberry pi library to display data on a 8-digit TM1638 seven segment module.
Dynamic install-able system level Raspberry Pi C++ library.

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
curl -sL https://github.com/gavinlyonsrepo/TM1638plus_RPI/archive/1.9.tar.gz | tar xz
```

4. Run "make" to run the makefile in base folder to install library, it will be
    installed to usr/lib and usr/include

```sh
cd TM1638plus_RPI-1.9
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

Hardware
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
Pictured at from left to right.

| Model No | Module Name | LEDS | Push buttons |
| ------ | ------ |  ------ | ------ |
| Model 1 | TM1638 LED & KEY | 8 red only | 8 |
| Model 2 | TM1638 KEYS, QYF  | 0 | 16 |
| Model 3 | TM1638 V1.3 or LKM1638  | 8 bi color,  red and green  | 8 |

![ module pics ](https://github.com/gavinlyonsrepo/TM1638plus/blob/master/extra/images/tm16383.jpg)

Notes
------------------------------

Note A : TM_Comm_Delay Communications optional delay

It may be necessary to adjust the define TM_Comm_Delay in the TM1638plus_common.h file It is Microsecond delay used in communications clocking, it is currently set to 1, It can be set to 0 or higher. On a different CPU Freq RPI it may be necessary to increase/decrease this.


See Also 
---------------------------------

This library is a port of my Arduino Library. There you will find the full documentation
including the API, which is near identical to RPI version except ::
 
	* Extra examples files for Arduino and examples are .ino files.
	* High freq data member flag is not needed in RPI library.
	* The text alignment enum has an extra enumerator for leading zeros.
	* Constructor has GPIO parameters in base class.
	* In file dependancy graphs ,High level file includes will differ. eg "#include <bcm2835.h>" will be missing.

[ Arduino github Link ](https://github.com/gavinlyonsrepo/TM1638plus)