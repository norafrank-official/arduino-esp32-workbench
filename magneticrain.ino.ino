#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
  FastLED.clear();
}

void loop() {
  binaryRain();
}

void binaryRain() {
  static uint32_t lastSpawn;
  const uint8_t FADE_AMOUNT = 32;
  
  fadeToBlackBy(leds, NUM_LEDS, FADE_AMOUNT);

  if(millis() - lastSpawn > 30) {
    leds[random16(NUM_LEDS)] = CRGB(175, 255, 175);
    lastSpawn = millis();
  }

  for(int i = NUM_LEDS-1; i > 0; i--) {
    leds[i] |= leds[i-1];
  }

  FastLED.show();
  FastLED.delay(50);
}