#include <FastLED.h>
#include <Servo.h>

#define LED_PIN     6
#define NUM_LEDS    120
#define TRIG_PIN    9
#define ECHO_PIN    10
#define BUZZER_PIN  8
#define SERVO_PIN   7

CRGB leds[NUM_LEDS];
Servo myservo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  myservo.attach(SERVO_PIN);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 1) { // Sweep from 0 to 180 degrees
    myservo.write(pos);
    checkDistance();
    delay(15); // Wait for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // Sweep back from 180 to 0 degrees
    myservo.write(pos);
    checkDistance();
    delay(15); // Wait for the servo to reach the position
  }
}

void checkDistance() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Convert to cm
  
  if (distance < 20) { // If an obstacle is detected within 20 cm
    digitalWrite(BUZZER_PIN, HIGH);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
    }
    FastLED.show();
    delay(100);
    FastLED.clear();
    FastLED.show();
    delay(100);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
  }
  delay(50); // Small delay to avoid excessive sensor readings
}
