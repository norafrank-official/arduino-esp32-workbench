#include "FastLED.h"

#define NUM_LEDS 120 // Adjust to match your 120 NeoPixel LEDs
#define PIN 6        // The pin connected to Din to control the LEDs

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500); // Set power limit of LED strip to 5V, 1500mA
  FastLED.clear();                                  // Initialize all LEDs to "OFF"
}

void loop() {
  fadeAnimation(255, 255, 255); // White
  fadeAnimation(255, 0, 0);     // Red
  // Add other colors as needed
}

void fadeAnimation(int red, int green, int blue) {
  float r, g, b;

  // FADE IN
  for (int i = 0; i <= 255; i++) {
    r = (i / 256.0) * red;
    g = (i / 256.0) * green;
    b = (i / 256.0) * blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }

  // FADE OUT
  for (int i = 255; i >= 0; i--) {
    r = (i / 256.0) * red;
    g = (i / 256.0) * green;
    b = (i / 256.0) * blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }
}

