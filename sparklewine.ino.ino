#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN 6
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 200

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  sparkleWineEffect();
  FastLED.show();
  delay(50);
}

void sparkleWineEffect() {
  // Randomly choose an LED to sparkle
  int pos = random(NUM_LEDS);
  leds[pos] = CRGB::Gold;

  // Fade all LEDs to create a sparkling effect
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(20);
  }
}
