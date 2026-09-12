#include <FastLED.h>

#define PIN 6          // Pin where the NeoPixel strip is connected
#define NUMPIXELS 120  // Number of LEDs in the strip
#define BRIGHTNESS  200
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUMPIXELS];

void setup() {
  FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(leds, NUMPIXELS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  fireworks();
  FastLED.show();
  delay(50);
}

void fireworks() {
  // Clear the strip
  fadeToBlackBy(leds, NUMPIXELS, 10);

  // Randomly choose a starting point for the firework
  int startPixel = random(NUMPIXELS);

  // Create the firework burst
  for (int i = 0; i < 10; i++) {
    int pixel = startPixel + i;
    if (pixel < NUMPIXELS) {
      leds[pixel] = CHSV(random(0, 255), 255, 255); // Random color
    }
    pixel = startPixel - i;
    if (pixel >= 0) {
      leds[pixel] = CHSV(random(0, 255), 255, 255); // Random color
    }
  }
}
