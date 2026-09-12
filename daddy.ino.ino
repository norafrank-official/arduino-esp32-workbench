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
  int blockSize = 4;
  int delayTime = 1;
  int waitTime = 100;
  int offTime = 500;

  int litLeds = 0;

  while (litLeds < NUM_LEDS) {
    for (int i = 0; i < NUM_LEDS; i += blockSize) {
      for (int k = 0; k < NUM_LEDS - litLeds; k++) {
        leds[k] = CRGB::Black;
      }

      for (int j = 0; j < blockSize; j++) {
        if (i + j < NUM_LEDS) {
          leds[i + j] = CRGB::Red;
        }
      }

      FastLED.show();
      delay(delayTime);

      if (i + blockSize >= NUM_LEDS) {
        litLeds += blockSize;
        break;
      }
    }
  }

  delay(waitTime);

  FastLED.clear();
  FastLED.show();
  delay(offTime);
}
