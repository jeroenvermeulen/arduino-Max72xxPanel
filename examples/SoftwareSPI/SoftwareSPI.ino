#include <SoftSPI.h>      // https://github.com/MajenkoLibraries/SoftSPI
#include <SPI.h>          // Arduino built-in
#include <Adafruit_GFX.h> // https://github.com/adafruit/Adafruit-GFX-Library
#include <Max72xxPanel.h> // https://github.com/Lithimlin/arduino-Max72xxPanel

int pinCS = 10;  // Attach CS to this pin
int pinMosi = 0; // Attach DIN to this pin
int pinSCLK = 4; // Attach CLK to this pin

int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, pinMosi, pinSCLK, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Using software SPI";
int wait = 20; // In milliseconds

void setup() {
  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness

  // The two for loops below may need to be modified
  // depending on the ordering and orientation of your displays

  // the setPosition function is responsible for the ordering of displays
  for(int i = 0; i < 4; i++) {
    matrix.setPosition(i, i, 0);  // The i'th display is at <i, 0>
  }

  // the setRotation function is responsible for the orientation of displays
  for(int i = 0; i < 8; i++) {
    matrix.setRotation(i, 1);     // rotate all displays 90 degrees
  }
}

void loop() {
  matrix.scrollDrawText(tape, wait);
}