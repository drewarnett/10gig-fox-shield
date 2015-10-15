/*
10 GHz Fox Shield KB9FKO

fox shield 1

  CW key down if rotary switch = 1
  else key up
 */

#define PIN_LED 13

#define PIN_KEY 1

#define PIN_KEY_DRO 11

#define PIN_MODE_3 7
#define PIN_MODE_2 6
#define PIN_MODE_1 5
#define PIN_MODE_0 4

void setup() {                
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_KEY, INPUT_PULLUP);

  pinMode(PIN_KEY_DRO, OUTPUT);
  
  pinMode(PIN_MODE_3, INPUT_PULLUP);
  pinMode(PIN_MODE_2, INPUT_PULLUP);
  pinMode(PIN_MODE_1, INPUT_PULLUP);
  pinMode(PIN_MODE_0, INPUT_PULLUP);  
}

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

void loop() {
  if (readMode() == 1)
  {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_KEY_DRO, HIGH);
  }
  else
  {
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_KEY_DRO, LOW);
  }
}
