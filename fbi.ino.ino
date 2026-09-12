#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    120
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FBI_Lights();
  FastLED.show();
  delay(50); // Adjust the delay to control the speed of the effect
}

void FBI_Lights() {
  static uint8_t hue = 0;
  static bool blinkState = false;

  for(int i = 0; i < NUM_LEDS; i++) {
    if(blinkState) {
      if((i / 10) % 2 == 0) {
        leds[i] = CRGB::Blue;
      } else {
        leds[i] = CRGB::Red;
      }
    } else {
      leds[i] = CRGB::Black; // Turn off LEDs during the blink
    }
  }

  blinkState = !blinkState; // Toggle the blink state
  hue += 1;
}
