#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    120
#define BRIGHTNESS  100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 == 0) {
      leds[i] = CRGB::Green;
    } else {
      leds[i] = CRGB::Red;
    }
  }
  FastLED.show();
  delay(500);

  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 == 0) {
      leds[i] = CRGB::Red;
    } else {
      leds[i] = CRGB::Green;
    }
  }
  FastLED.show();
  delay(500);
}

