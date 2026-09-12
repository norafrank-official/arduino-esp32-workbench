#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// Matrix-style parameters
const uint8_t FADE_AMOUNT = 32;
const uint16_t SPAWN_INTERVAL = 30;

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
  
  // Fade all pixels
  fadeToBlackBy(leds, NUM_LEDS, FADE_AMOUNT);

  // Spawn new drops
  if(millis() - lastSpawn > SPAWN_INTERVAL) {
    leds[random16(NUM_LEDS)] = CRGB(175, 255, 175);  // Pale green
    lastSpawn = millis();
  }

  // Cascade effect
  for(int i = NUM_LEDS-1; i > 0; i--) {
    leds[i] |= leds[i-1];  // Carry brightness downward
  }

  // Random twinkle
  if(random8() < 40) {
    leds[random16(NUM_LEDS)] = CRGB::White;
  }

  FastLED.show();
  FastLED.delay(50);
}