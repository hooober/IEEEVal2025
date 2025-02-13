// GCC Valentines 2025 Example Code

/* everything from here down should be copied */

#include <FastLED.h>
#include "2_Heart_Rainbow.h"

// LED constants
#define NUM_LEDS 25
#define LEDS_PIN 4

// array that holds all our LEDs
CRGB leds[NUM_LEDS];

// Button Constants
#define BUTTON_PIN 3

void setup() {
  // adding our LEDs to the library
  FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);

  // setting our Brightness to be 1/4 globally (64/256)
  FastLED.setBrightness(5);

  // set up our button to be an input
  pinMode(BUTTON_PIN, INPUT);

  // calling our setup code for our different modes
  LED_rainbow_setup();
  static_heart_setup();
  heart_rainbow_setup();
}

int mode = 0; // controls which mode we are in

void loop() {

  if (digitalRead(BUTTON_PIN)) {
    mode = (mode + 1) % 3; // increase our mode and wrap
                           // it back to 0 when we hit 3
    delay(1000); // debounce the button
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black);

  switch(mode) { // choose the mode and run it
    case 0:
      LED_rainbow_loop();
      break;
    case 1:
      static_heart_loop();
      break;
    case 2:
      heart_rainbow_loop();
      break;
  }
}

