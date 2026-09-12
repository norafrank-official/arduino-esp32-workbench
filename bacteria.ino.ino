#include <FastLED.h>

// LED Configuration
#define NUM_LEDS 120
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

// Bacterial Colony Parameters
const uint8_t SPREAD_RATE = 24;
const uint8_t MAX_DENSITY = 150;
const uint8_t DECAY_RATE = 1;
const uint8_t SEED_CHANCE = 12;  // Higher = more colony starts

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);  // Adjust brightness here (0-255)
  FastLED.clear();
}

void loop() {
  bacterialColony();
}

void bacterialColony() {
  static uint8_t density[NUM_LEDS] = {0};
  
  // 1. Seed new colonies randomly
  if(random8() < SEED_CHANCE) {
    uint16_t pos = random16(NUM_LEDS);
    density[pos] = MAX_DENSITY;
  }

  // 2. Spread existing colonies
  for(int i = 0; i < NUM_LEDS; i++) {
    if(density[i] >= 30) {
      // Spread to left neighbor
      if(i > 0) density[i-1] = qadd8(density[i-1], SPREAD_RATE);
      // Spread to right neighbor
      if(i < NUM_LEDS-1) density[i+1] = qadd8(density[i+1], SPREAD_RATE);
    }
  }

  // 3. Update LEDs and decay colonies
  for(int i = 0; i < NUM_LEDS; i++) {
    // Apply density decay
    density[i] = qsub8(density[i], DECAY_RATE);
    
    // Convert density to color (greenish with yellow highlights)
    uint8_t hue = 95 + (density[i] / 8);  // Color variation
    uint8_t val = density[i];             // Direct brightness mapping
    leds[i] = CHSV(hue, 255, val);
  }

  FastLED.show();
  FastLED.delay(50);  // Adjust speed here
}