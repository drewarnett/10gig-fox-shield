/*
10 GHz Fox Shield KB9FKO

fox shield 3

  CW key down if rotary switch = 1
  AM key down 300 Hz if rotary switch = 2
  AM key down 500 Hz if rotary switch = 3
  AM key down 700 Hz if rotary switch = 4
  AM key down 1100 Hz if rotary switch = 5
  CW via key input if rotary switch = 6
  MCW 500 Hz via key input if rotary switch = 7
  MCW 700 Hz via key input if rotary switch = 8
  AM CW beacon "A" 300 Hz if rotary switch = 0xA
  AM CW beacon "B" 500 Hz if rotary switch = 0xB
  AM CW beacon "C" 700 Hz if rotary switch = 0xC
  AM CW beacon "D" 1100 Hz if rotary switch = 0xD
  
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

char * lookup(char c) {
  switch (c) {
    case ' ':  return " "; break;
    case 'a':  return ".-"; break;
    case 'b':  return "-..."; break;
    case 'c':  return "-.-."; break;
    case 'd':  return "-.."; break;
    case 'e':  return "."; break;
    case 'f':  return "..-."; break;
    case 'g':  return "--."; break;
    case 'h':  return "...."; break;
    case 'i':  return ".."; break;
    case 'j':  return ".---"; break;
    case 'k':  return "-.-"; break;
    case 'l':  return ".-.."; break;
    case 'm':  return "--"; break;
    case 'n':  return "-."; break;
    case 'o':  return "---"; break;
    case 'p':  return ".--."; break;
    case 'q':  return "--.-"; break;
    case 'r':  return ".-."; break;
    case 's':  return "..."; break;
    case 't':  return "-"; break;
    case 'u':  return "..-"; break;
    case 'v':  return "...-"; break;
    case 'w':  return ".--"; break;
    case 'x':  return "-..-"; break;
    case 'y':  return "-.--"; break;
    case 'z':  return "--.."; break;
    
    default:  break;
  }
}

void send(char * s, int freq, int wpm)
{
  float dit_time = (60./50)/wpm;
  float dah_time = 3*dit_time;
  float intrachar_time = dit_time;
  float interchar_time = dah_time;
  float interword_time = 7*dit_time;

  char * elements;
  
  for (int i=0; i < strlen(s); i++) {
    elements = lookup(s[i]);
    for (int j=0; j < strlen(elements); j++) {
      switch(elements[j]) {
        case ' ':
          delay(1000*(interword_time - interchar_time));  // only 1 element in this case
          break;
        case '-':
          keydown_am(freq);
          delay(1000*dah_time);
          keyup();
          delay(1000*intrachar_time);
          break;
        case '.':
          keydown_am(freq);
          delay(1000*dit_time);
          keyup();
          delay(1000*intrachar_time);
          break;
        default:
          break;
      }
    }
    delay(1000*(interchar_time - intrachar_time)); 
  }
}
  
int mode;
int lastMode;
int key;
int lastkey;

void setup() {                
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_KEY, INPUT_PULLUP);

  pinMode(PIN_KEY_DRO, OUTPUT);
  
  pinMode(PIN_MODE_3, INPUT_PULLUP);
  pinMode(PIN_MODE_2, INPUT_PULLUP);
  pinMode(PIN_MODE_1, INPUT_PULLUP);
  pinMode(PIN_MODE_0, INPUT_PULLUP);
  
  lastMode = -1;
  lastkey = 0;
}

void loop() {
  mode = readMode();
  switch(mode) {
    case 1:
      if (mode != lastMode) keydown();
      break;
    case 2:
      if (mode != lastMode) keydown_am(300);
      break;
    case 3:
      if (mode != lastMode) keydown_am(500);
      break;
    case 4:
      if (mode != lastMode) keydown_am(700);
      break;
    case 5:
      if (mode != lastMode) keydown_am(1100);
      break;
    case 6:
      if (mode != lastMode)
      {
        keyup();
        lastkey = 0;
      }
      key = readKey();
      if (key != lastkey) {
        if (key) keydown();
        else keyup();
        lastkey = key;
      }
      break;
    case 7:
      if (mode != lastMode)
      {
        keyup();
        lastkey = 0;
      }
      key = readKey();
      if (key != lastkey) {
        if (key) keydown_am(500);
        else keyup();
        lastkey = key;
      }
      break;
    case 8:
      if (mode != lastMode)
      {
        keyup();
        lastkey = 0;
      }
      key = readKey();
      if (key != lastkey) {
        if (key) keydown_am(700);
        else keyup();
        lastkey = key;
      }
      break;
    case 0xa:
      send("a", 300, 5);
      break;
    case 0xb:
      send("b", 500, 5);
      break;
    case 0xc:
      send("c", 700, 5);
      break;
    case 0xd:
      send("d", 1100, 5);
      break;
    default:
      keyup();
      break;
    }
  lastMode = mode;
}
