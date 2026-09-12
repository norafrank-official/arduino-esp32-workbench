int ledPins[] = {2, 3, 4, 5, 6}; // Replace with your LED pin numbers

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.read() - '0'; // Convert incoming character to integer
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], bitRead(data, i));
    }
  }
}