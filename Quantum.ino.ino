#include <FastLED.h>
#define NUM_LEDS 120
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void quantumTunnel() {
  static uint16_t offset;
  static uint8_t hue;
  for(int i = 0; i < NUM_LEDS; i++) {
    // Warping effect with multiple frequency waves
    int value = (sin8(i * 4 + offset) + cos8(i * 8 - offset*2)) / 2;
    leds[i] = CHSV(hue + (i * 2), 255, value);
  }
  offset += 6;
  hue += 2;
  FastLED.show();
  FastLED.delay(20);
}

void loop() {
  quantumTunnel();
}