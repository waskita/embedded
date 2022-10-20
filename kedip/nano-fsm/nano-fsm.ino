#define ON    100
#define OFF   101

#define LED_OUTPUT 3
int state = OFF;

void fsm_init(int *state) {
  *state = OFF;
}

void fsm(int  *state, int *out) {
  switch (*state) {
    case ON: {
        *state = OFF;
        *out = 0;
        break;
      }
    case OFF: {
        *state = ON;
        *out = 1; // nyalakan output
        break;
      }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  Serial.begin(115200);
  fsm_init(&state);
}

void loop() {
  int output=0;
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

  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);                       //
  digitalWrite(LED_BUILTIN, HIGH);
}
