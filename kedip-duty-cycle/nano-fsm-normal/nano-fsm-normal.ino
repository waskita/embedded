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

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void fsm(int  *state, int *output) {
  switch (*state) {
    case ON: {
        *state = OFF_1;
        *output = 0;
        break;
      }
    case OFF_1: {
        *state = OFF_2;
        *output = 0;
        break;
      }
    case OFF_2: {
        *state = OFF_3;
        *output = 0;
        break;
      }
    case OFF_3: {
        *state = OFF_4;
        *output = 0;
        break;
      }
    case OFF_4: {
        *state = OFF_5;
        *output = 0;
        break;
      }
    case OFF_5: {
        *state = OFF_6;
        *output = 0;
        break;
      }
    case OFF_6: {
        *state = OFF_7;
        *output = 0;
        break;
      }
    case OFF_7: {
        *state = OFF_8;
        *output = 0;
        break;
      }
    case OFF_8: {
        *state = OFF_9;
        *output = 0;
        break;
      }
    case OFF_9: {
        *state = ON;
        *output = 1;
        break;
      }
  }
}
// the loop function runs over and over again forever
int state = OFF_9;
int output;
void loop() {
  fsm(&state, &output);
  if (output == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

  delay(500);                       // wait for 1 second
}
