#include <FastLED.h>

#define LED_PIN 6  // Pin where the LED strip is connected
#define NUM_LEDS 120  // Number of LEDs in the strip
#define BUZZER_PIN 9  // Pin where the buzzer is connected

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'G') {
      setStripColor(CRGB::Green);  // Green
    } else if (command == 'R') {
      setStripColor(CRGB::Red);  // Red
      tone(BUZZER_PIN, 1000, 500);  // Play sound for 500ms
    } else if (command == 'O') {
      turnOffStrip();  // Turn off LEDs
    }
  }
}

void setStripColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void turnOffStrip() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
