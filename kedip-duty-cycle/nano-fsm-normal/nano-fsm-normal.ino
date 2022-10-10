#define ON    100
#define OFF_1 101
#define OFF_2 102
#define OFF_3 103
#define OFF_4 104
#define OFF_5 105
#define OFF_6 106
#define OFF_7 107
#define OFF_8 108
#define OFF_9 109

#define LED_OUTPUT 3

int state = OFF_9;

void fsm_init(int *state) {
  *state = OFF_9;
}

void fsm(int  *state, int *out) {
  switch (*state) {
    case ON: {
        *state = OFF_1;
        *out = 0;
        break;
      }
    case OFF_1: {
        *state = OFF_2;
        *out = 0;
        break;
      }
    case OFF_2: {
        *state = OFF_3;
        *out = 0;
        break;
      }
    case OFF_3: {
        *state = OFF_4;
        *out = 0;
        break;
      }
    case OFF_4: {
        *state = OFF_5;
        *out = 0;
        break;
      }
    case OFF_5: {
        *state = OFF_6;
        *out = 0;
        break;
      }
    case OFF_6: {
        *state = OFF_7;
        *out = 0;
        break;
      }
    case OFF_7: {
        *state = OFF_8;
        *out = 0;
        break;
      }
    case OFF_8: {
        *state = OFF_9;
        *out = 0;
        break;
      }
    case OFF_9: {
        *state = ON;
        *out = 1;
        break;
      }
  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  Serial.begin(115200);
  fsm_init(&state);
}

void loop() {
  int output;
  fsm(&state, &output);
  if (output == 1) {
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    digitalWrite(LED_OUTPUT, LOW);
  }
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

  delay(500);                       //
//  digitalWrite(LED_BUILTIN, LOW);
  delay(500);                       //
//  digitalWrite(LED_BUILTIN, HIGH);
}
