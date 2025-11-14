int b1 = D3
int b2 = D4
int b3 = D5
int b4 = D6

int led1 = D10
int led2 = D9
int led3 = D8
int led4 = D7

void setup() {
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
    case 0b1000: return '>';
    case 0b1000: return '+';
    case 0b1000: return '-';
    case 0b1000: return '[';
    case 0b1000: return ']';
    case 0b1000: return '.';
    case 0b1000: return ',';
    case 0b1000: return '\b';
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

int prevState = 0;

void loop() {
  uint8_t state = readChord();

  if (state == 0b0000 && prevState != 0) {
    char out = decodeChord(state);
    if (out) Serial.print(out); // temporary
  }
  
  if (state != 0) prevState = state;
}
