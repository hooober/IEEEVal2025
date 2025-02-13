#include "2_Heart_Rainbow.h"

#define NUM_PATH_LEDS 10

CRGB rainbow[NUM_PATH_LEDS]; // will be filled with rainbow colors
                             //
                             // we will pull our LED colors from this array

CRGB* path_leds[NUM_LEDS]; // holds the leds in the path's index


void heart_rainbow_setup() {
  fill_rainbow_circular(rainbow, NUM_PATH_LEDS, 0); // fills our rainbow array

  /* precalculate our path LEDs */

  // see 2_Heart_Rainbow.h for the declaration of coord_t
  // Arduino is weird about multiple files
  // typedef struct {
  //   uint8_t x;
  //   uint8_t y;
  // } coord_t;

  // the image we want to make
  // | X X |
  // |X X X|
  // |X   X|
  // | X X |
  // |  X  |
  // coords contains the LEDs on our path
  // coords is 0, 0 in the top left part of the image
  // basically meaning we can treat the LEDs like a 2D array
  coord_t coords[] = {
  {2, 1}, {3, 0}, {4, 1}, // starting at top-most middle to top-most right
  {4, 2}, {3, 3}, {2, 4}, // from top-most right to bottom-most right
  {1, 3}, {0, 2}, {0, 1}, // from bottom-most right to top-most left
  {1, 0} // from top-most left ot top-most middle
  };

  for (int i = 0; i < NUM_PATH_LEDS; i++) {
    uint8_t led_index = coordsToFlat(coords[i]);
    path_leds[i] = &(leds[led_index]);
  }
}

/* help us keep track of where we are in rainbow */
uint8_t start_rainbow_index = 0; // holds the index we will start at each loop
uint8_t current_rainbow_index = 0; // holds the next index to iterate to

// used to convert coords to pixel index
// where x=0, y=0 correspond to the top left corner
// and x=4, y=0 correspond to the top right corner
uint8_t coordsToFlat(coord_t coord) {
  return 5 * coord.y + coord.x;
}

void heart_rainbow_loop() {
  /* set all the colors of the LEDs using rainbow and the indicies*/
    for (int i = 0; i < NUM_PATH_LEDS; i++) {
      CRGB value = rainbow[current_rainbow_index];

      *path_leds[i] = rainbow[current_rainbow_index]; // set the LEDs to their color

      start_rainbow_index = current_rainbow_index; // saving previous value for next loop
      current_rainbow_index = (current_rainbow_index + 1) % NUM_PATH_LEDS; // inc by one, while
                                                                          // wrapping the index
                                                                          // around when we hit
                                                                          // the end of rainbow

    }

    current_rainbow_index = start_rainbow_index; // ring loop, make us start on the pixel
                                                // color of the last pixel's value

    FastLED.show(); // necessary, (write to pixels)
    delay(500); // give us time to enjoy
}