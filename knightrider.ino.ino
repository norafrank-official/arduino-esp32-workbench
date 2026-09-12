#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN 6 // Change this to the actual pin connected to your LED strip

CRGB leds[NUM_LEDS];

void knightRider(int red, int green, int blue, int ridingWidth, int delayDuration, int returnDelayDuration) {
  for (int i = 0; i < (NUM_LEDS - ridingWidth - 2); i++) {
    FastLED.clear();
    leds[i] = CRGB(red / 10, green / 10, blue / 10);
    for (int j = 1; j <= ridingWidth; j++) {
      leds[i + j] = CRGB(red, green, blue);
    }
    leds[i + ridingWidth + 1] = CRGB(red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(delayDuration);
  }

  delay(returnDelayDuration);

  for (int i = (NUM_LEDS - ridingWidth - 2); i > 0; i--) {
    FastLED.clear();
    leds[i] = CRGB(red / 10, green / 10, blue / 10);
    for (int j = 1; j <= ridingWidth; j++) {
      leds[i + j] = CRGB(red, green, blue);
    }
    leds[i + ridingWidth + 1] = CRGB(red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(delayDuration);
  }

  delay(returnDelayDuration);
}

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Adjust brightness (0-255)
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Call the knightRider function with desired parameters
  knightRider(255, 0, 0, 5, 50, 1000);
  knightRider(0, 255, 0, 5, 50, 1000);
  knightRider(0, 0, 255, 5, 50, 1000); // Red, ridingWidth = 5, delayDuration = 50ms, returnDelayDuration = 1000ms
}

