#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    120
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  createBlock(CRGB::Yellow);
  createBlock(CRGB::White);
  createBlock(CRGB::Green);
  createBlock(CRGB::Orange);
}

void createBlock(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    delay(50); // Adjust delay for speed of block movement
  }
  delay(500); // Pause before starting the next block
}
