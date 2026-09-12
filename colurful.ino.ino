#include <FastLED.h>

#define NUM_LEDS 120
#define PIN 6

// Define the 8 colors you want to use
CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Purple, CRGB::Orange, CRGB::White, CRGB::Teal};

// Global variable to store the LED strip
CRGB leds[NUM_LEDS];

// Function to create the twinkling star effect
void twinkleStars(int numLeds) {
  for (int i = 0; i < numLeds; i++) {
    // Randomly choose a color and brightness for the LED
    int randomColor = random(0, 8);
    int randomBrightness = random(10, 255);

    // Set the LED's color and brightness
    leds[i] = colors[randomColor];
    leds[i].maximizeBrightness();
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
}

void loop() {
  // Create the twinkling star effect
  twinkleStars(NUM_LEDS);

  // Show the LED strip
  FastLED.show();

  // Delay for a short time
  delay(100);
}