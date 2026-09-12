#include <FastLED.h>

#define NUM_LEDS 120
#define PIN 6

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(128); // Adjust brightness as needed
}

void loop() {
  // Create a random starting position
  int startPosition = random(NUM_LEDS);

  // Define the length of the shooting star
  int starLength = random(5, 20);

  // Create a random color for the star
  CRGB starColor = CRGB(random(255), random(255), random(255));

  // Animate the shooting star
  for (int i = startPosition; i < startPosition + starLength; i++) {
    leds[i] = starColor;
    FastLED.show();
    delay(50); // Adjust delay for speed
    leds[i] = CRGB::Black;
  }
}