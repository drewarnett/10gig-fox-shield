/*
10 GHz Fox Shield KB9FKO

fox shield 2

  CW key down if rotary switch = 1
  AM key down 300 Hz if rotary switch = 2
  AM key down 500 Hz if rotary switch = 3
  AM key down 700 Hz if rotary switch = 4
  AM key down 1100 Hz if rotary switch = 5
  
  else key up
 */

#define PIN_LED 13

#define PIN_KEY 1

#define PIN_KEY_DRO 11

#define PIN_MODE_3 7
#define PIN_MODE_2 6
#define PIN_MODE_1 5
#define PIN_MODE_0 4

int readMode(void)
{
  return (
    (digitalRead(PIN_MODE_3) ? 0 : 1<<3) +
    (digitalRead(PIN_MODE_2) ? 0 : 1<<2) +
    (digitalRead(PIN_MODE_1) ? 0 : 1<<1) +
    (digitalRead(PIN_MODE_0) ? 0 : 1<<0)
    );
}

int readKey(void)
{
  return !(digitalRead(PIN_KEY) == HIGH);
}

void keyup() {
  noTone(PIN_KEY_DRO);
  digitalWrite(PIN_KEY_DRO, LOW);
  digitalWrite(PIN_LED, LOW);
}

void keydown() {
  digitalWrite(PIN_LED, HIGH);
  noTone(PIN_KEY_DRO);
  digitalWrite(PIN_KEY_DRO, HIGH);
}

void keydown_am(int freq) {
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_KEY_DRO, LOW);
  tone(PIN_KEY_DRO, freq);
}

int mode;
int lastMode;

void setup() {                
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_KEY, INPUT_PULLUP);

  pinMode(PIN_KEY_DRO, OUTPUT);
  
  pinMode(PIN_MODE_3, INPUT_PULLUP);
  pinMode(PIN_MODE_2, INPUT_PULLUP);
  pinMode(PIN_MODE_1, INPUT_PULLUP);
  pinMode(PIN_MODE_0, INPUT_PULLUP);
  
  lastMode = -1;
}

void loop() {
  mode = readMode();
  if (mode != lastMode) {
    lastMode = mode;
    switch(mode) {
      case 1:
        keydown();
        break;
      case 2:
        keydown_am(300);
        break;
      case 3:
        keydown_am(500);
        break;
      case 4:
        keydown_am(700);
        break;
      case 5:
        keydown_am(1100);
        break;
      default:
        keyup();
        break;
    }
  }
}
