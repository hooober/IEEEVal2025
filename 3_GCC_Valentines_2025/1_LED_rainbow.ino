void LED_rainbow_setup() {
}


void LED_rainbow_loop() {
  // fill our leds with a rainbow
  fill_rainbow_circular(leds, NUM_LEDS, 0);
  FastLED.show();
}