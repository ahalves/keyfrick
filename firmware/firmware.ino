#include <Keyboard.h>

int b1 = D3;
int b2 = D4;
int b3 = D5;
int b4 = D6;

int led1 = D10;
int led2 = D9;
int led3 = D8;
int led4 = D7;

unsigned long debounce = 50;
uint8_t lastState = 0;
uint8_t stableState = 0;
unsigned long lastChangeTime = 0;

void setup() {

  Keyboard.begin();

  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

char decodeChord(uint8_t chord) {
  switch (chord) {
    case 0b1000: return '<';
    case 0b0001: return '>';
    case 0b0100: return '+';
    case 0b0010: return '-';
    case 0b1100: return '[';
    case 0b0011: return ']';
    case 0b1010: return '.';
    case 0b0101: return ',';
    case 0b1111: return '\b';
    default:     return 0;
  }
}

uint8_t readChord() {
  uint8_t chord = 0;

  chord |= (digitalRead(b1) == LOW) << 3;
  chord |= (digitalRead(b2) == LOW) << 2;
  chord |= (digitalRead(b3) == LOW) << 1;
  chord |= (digitalRead(b4) == LOW) << 0;

  return chord;
}

void loop() {
  uint8_t currentState = readChord();

  digitalWrite(led1, (currentState & 0b1000) ? HIGH : LOW);
  digitalWrite(led2, (currentState & 0b0100) ? HIGH : LOW);
  digitalWrite(led3, (currentState & 0b0010) ? HIGH : LOW);
  digitalWrite(led4, (currentState & 0b0001) ? HIGH : LOW);

  if (currentState != lastState) lastChangeTime = millis();

  if (millis() - lastChangeTime > debounce) {
    if (currentState != stableState) {
      stableState = currentState;

      if (stableState == 0b0000 && lastState != 0b0000) {
        char out = decodeChord(lastState);
        if (out) Keyboard.write(out);
      }
    }
  }

  lastState = currentState;
}
