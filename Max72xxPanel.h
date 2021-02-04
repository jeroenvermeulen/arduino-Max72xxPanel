/******************************************************************
 A library for controling a set of 8x8 LEDs with a MAX7219 or
 MAX7221 displays.

 This is a plugin for Adafruit's core graphics library, providing
 basic graphics primitives (points, lines, circles, etc.).
 You need to download and install Adafruit_GFX to use this library.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!

 Written by Mark Ruys, 2013.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.

 Datasheet: http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

 ******************************************************************/
#define SOFTSPI // Disabling saves 252 bytes of memory

#ifndef Max72xxPanel_h
#define Max72xxPanel_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <SPI.h>
#ifdef SOFTSPI
#include <SoftSPI.h> // https://github.com/MajenkoLibraries/SoftSPI
#endif

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include "pins_arduino.h"
#endif

class Max72xxPanel : public Adafruit_GFX {

public:

  /*
   * Create a new controler - Hardware SPI
   * Parameters:
   * csPin		pin for selecting the device
   * hDisplays  number of displays horizontally
   * vDisplays  number of displays vertically
   */
  Max72xxPanel(byte csPin, byte hDisplays=1, byte vDisplays=1);

  /*
   * Create a new controler - Software SPI
   * Parameters:
   * csPin		  pin for selecting the device, CS/SS
   * mosiPin		pin for data from master, MOSI/DIN
   * sclkPin    pin for serial clock, SCLK/CLK/SCK
   * hDisplays  number of displays horizontally
   * vDisplays  number of displays vertically
   */
  #ifdef SOFTSPI
  Max72xxPanel(byte csPin, byte mosiPin, byte sclkPin, byte hDisplays, byte vDisplays);
  #endif

	/*
	 * Define how the displays are ordered. The first display (0)
	 * is the one closest to the Arduino.
	 */
	void setPosition(byte display, byte x, byte y);

	/*
	 * Define if and how the displays are rotated. The first display
	 * (0) is the one closest to the Arduino. rotation can be:
	 *   0: no rotation
	 *   1: 90 degrees clockwise
	 *   2: 180 degrees
	 *   3: 90 degrees counter clockwise
	 */
	void setRotation(byte display, byte rotation);

	/*
	 * Implementation of Adafruit's setRotation(). Probably, you don't
	 * need this function as you can achieve the same result by using
	 * the previous two functions.
	 */
	void setRotation(byte rotation);

  /*
   * Draw a pixel on your canvas. Note that for performance reasons,
   * the pixels are not actually send to the displays. Only the internal
   * bitmap buffer is modified.
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);

  /*
   * As we can do this much faster then setting all the pixels one by
   * one, we have a dedicated function to clear the screen.
   * The color can be 0 (blank) or non-zero (pixel on).
   */
  void fillScreen(uint16_t color);

  /*
   * Set the shutdown (power saving) mode for the device
   * Paramaters:
   * status	If true the device goes into power-down mode. Set to false
   *		for normal operation.
   */
  void shutdown(boolean status);

  /*
   * Set the brightness of the display.
   * Paramaters:
   * intensity	the brightness of the display. (0..15)
   */
  void setIntensity(byte intensity);

  /*
   * After you're done filling the bitmap buffer with your picture,
   * send it to the display(s).
   */
  void write();

  /*
   * Writes a tape to the display in scrolling text format
   * Parameters:
   * tape the string to be printed
   * wait the delay between two steps while scrolling
   * letter_width the width of the letters. Default is 6
   * spacer the space between two letters. Default is 1
   * color  the color of the text. Either HIGH or LOW. Default is HIGH
   * bg the background of the text. Either HIGH or LOW. Default is LOW
   * size the size of the text. Default is 1
   */
  void scrollDrawText(String tape, uint16_t wait = 45, uint8_t letter_width = 6, uint8_t spacer = 1, uint16_t color = HIGH, uint16_t bg = LOW, uint8_t size = 1);

private:
  byte SPI_CS;       /* SPI:     pin for CS            */
#ifdef SOFTSPI
  byte SSPI_MOSI=-1; /* SoftSPI: pin for MOSI/Data/DIN */
  byte SSPI_MISO=-1; /* SoftSPI: pin for MISO          */
  byte SSPI_SCLK=-1; /* SoftSPI: pin for SCLK/Clock    */
#endif

  /* Initialize the driver */
  void initialize(byte hDisplays=1, byte vDisplays=1);

  /* Send out a single command to the device */
  void spiTransfer(byte opcode, byte data=0);

  /* We keep track of the led-status for 8 devices in this array */
  byte *bitmap;
  byte bitmapSize;

  byte hDisplays;
  byte *matrixPosition;
  byte *matrixRotation;

#ifdef SOFTSPI
  SoftSPI* softSPI;
#endif
};

#endif	// Max72xxPanel_h
