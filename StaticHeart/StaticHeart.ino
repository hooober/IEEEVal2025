
// the image we want to use
bool static_heart[25] = {
  0, 1, 0, 1, 0,
  1, 0, 1, 0, 1,
  1, 0, 0, 0, 1,
  0, 1, 0, 1, 0,
  0, 0, 1, 0, 0,
};

void static_heart_setup() {
}

void static_heart_loop() {
  // set the colors of the LEDs
  // this will make anything in the array that is a '1' the color we want
  for (int i = 0; i < NUM_LEDS; i++) {
    if (static_heart[i]) { // checking if we have a '1'
      leds[i] = CRGB::Purple; // color, see FastLED doc for more predefined colors
    }
  }

  // show our LEDs
  FastLED.show();
}