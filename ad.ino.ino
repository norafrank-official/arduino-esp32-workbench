#include <MD_MAX72XX.h>
#include <SPI.h>

#define MAX_DEVICES 4
#define CS_PIN 10

MD_MAX72XX display = MD_MAX72XX(MD_MAX72XX::FC16_HW, CS_PIN, MAX_DEVICES);

const char* adText = "Hello World!";
int scrollPosition = 0;
const int CHAR_WIDTH = 8;

void setup() {
  display.begin();
  display.clear();
}

void scrollText() {
  for (int i = (MAX_DEVICES * 8) - 1; i > 0; i--) {
    display.setColumn(i, display.getColumn(i - 1));
  }

  int charIndex = scrollPosition / CHAR_WIDTH;
  char currentChar = adText[charIndex % strlen(adText)];

  for (int segment = 0; segment < CHAR_WIDTH; segment++) {
    uint8_t colData = getCharColumn(currentChar, segment); // You must implement this
    display.setColumn(0, colData);
  }

  display.setColumn(0, 0);  // space between characters
  scrollPosition++;
}

// You need to define or replace getCharColumn()
