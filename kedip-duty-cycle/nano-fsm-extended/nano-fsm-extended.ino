#define ON    100
#define OFF   101
#define OUTPUT_LED 12
int state = ON;
int output = 1;
int counter = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(OUTPUT_LED, OUTPUT);
  Serial.begin(115200);

  fsm_init();
  delay(1000);
}

void fsm_init() {
  state = ON;
  output = 1;
}
void fsm(int  *state, int *output, int *counter) {
  switch (*state) {
    case ON: {
        *state = OFF;
        *output = 0;
        *counter = 0;
        break;
      }
    case OFF: {
        if (*counter == 9) {
          *state = ON;
          *output = 1;
          *counter++;
        } else {
          *state = OFF;
          *output = 0;
          *counter = *counter + 1;
        }
        break;
      }
  }
}

void loop() {
  fsm(&state, &output, &counter);
  if (output == 1) {
    digitalWrite(OUTPUT_LED, HIGH);
  } else {
    digitalWrite(OUTPUT_LED, LOW);
  }
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" counter: ");
  Serial.print(counter);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

  delay(1000);                       // wait for 1 second
}
