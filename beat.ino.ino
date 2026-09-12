#include <FastLED.h>

// Hardware Configuration
#define LED_PIN     6
#define MIC_PIN     A0
#define NUM_LEDS    120
#define SAMPLE_WINDOW 20   // ms for audio sampling

CRGB leds[NUM_LEDS];

// 10-Color Palette (16 colors required for CRGBPalette16)
const CRGBPalette16 palette = CRGBPalette16(
  // Primary 10 colors
  CRGB(255, 0, 0),    // Red
  CRGB(0, 255, 0),    // Green
  CRGB(0, 0, 255),    // Blue
  CRGB(255, 255, 0),  // Yellow
  CRGB(255, 0, 255),  // Magenta
  CRGB(0, 255, 255),  // Cyan
  CRGB(255, 128, 0),  // Orange
  CRGB(128, 0, 255),  // Purple
  CRGB(255, 255, 255),// White
  CRGB(128, 255, 0),  // Lime
  
  // Additional 6 colors (repeats from start)
  CRGB(255, 0, 0),    // Red
  CRGB(0, 255, 0),    // Green
  CRGB(0, 0, 255),    // Blue
  CRGB(255, 255, 0),  // Yellow
  CRGB(255, 0, 255),  // Magenta
  CRGB(0, 255, 255)   // Cyan
);

// Beat detection variables
unsigned long lastSample = 0;
int baseline = 512;      // ADC center point (2.5V)
int threshold = 80;      // Variable threshold (was #define)
float avgEnvelope = 80;  // Initialize average

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  Serial.begin(115200);
}

void loop() {
  // 1. Read microphone and detect beats
  int micValue = analogRead(MIC_PIN);
  int envelope = abs(micValue - baseline);
  
  if (millis() - lastSample > SAMPLE_WINDOW) {
    lastSample = millis();
    
    // 2. Update dynamic threshold
    avgEnvelope = 0.7 * avgEnvelope + 0.3 * envelope;
    threshold = avgEnvelope * 1.5;  // Now works with variable
    
    // 3. Trigger effect on beat
    if (envelope > threshold) {
      visualizeBeat();
    }
  }

  // 4. Baseline tracking (DC offset)
  baseline = 0.999 * baseline + 0.001 * micValue;
  
  // 5. Fade all LEDs for trailing effect
  fadeToBlackBy(leds, NUM_LEDS, 25);
  FastLED.show();
}

// Visualization effects on beat detection
void visualizeBeat() {
  static uint8_t colorIndex = 0;
  
  // Effect 1: Center pulse
  fill_solid(leds + 50, 20, ColorFromPalette(palette, colorIndex));
  
  // Effect 2: Moving bars
  for (int i = 0; i < 4; i++) {
    int pos = beatsin16(20 + i * 5, 0, NUM_LEDS - 10);
    fill_solid(leds + pos, 10, ColorFromPalette(palette, colorIndex + i * 25));
  }
  
  // Effect 3: Peripheral sparks
  leds[random16(NUM_LEDS)] = ColorFromPalette(palette, colorIndex + 128);
  leds[random16(NUM_LEDS)] = ColorFromPalette(palette, colorIndex + 192);

  colorIndex += 32;  // Cycle through palette
}