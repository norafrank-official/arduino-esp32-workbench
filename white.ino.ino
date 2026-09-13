#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN 6
#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];

const int numMovingLEDs = 4; // Number of LEDs to light up at a time

int litLEDs = numMovingLEDs; // Keeps track of the number of currently lit LEDs

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Light up the current number of LEDs
  for (int i = 0; i < litLEDs; i++) {
    leds[i] = CRGB::White;
  }

  // Check if all LEDs are lit
  if (litLEDs == NUM_LEDS) {
    delay(1000); // Hold for 1 second at the end
    litLEDs = 0; // Reset for next loop
  } else {
    litLEDs++; // Increase the number of lit LEDs for next iteration
  }

  FastLED.show();
  delay(100);
}
