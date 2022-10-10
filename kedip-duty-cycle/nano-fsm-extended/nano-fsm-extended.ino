#define ON    100
#define OFF   101
#define OUTPUT_LED 3
int state = ON;
int count = 0;
int output = 1;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(OUTPUT_LED, OUTPUT);
  Serial.begin(115200);

  fsm_init(&state, &output, &count);
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" count: ");
  Serial.print(count);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

  delay(1000);
}

void fsm_init(int  *state, int *output, int *count) {
  state = ON;
  *output = 1;
  *count = 0;
}
void fsm(int  *state, int *output, int *count) {
  switch (*state) {
    case ON: {
        *state = OFF;
        *output = 0;
        *count = 0;
        break;
      }
    case OFF: {
        if (*count == 9) {
          *state = ON;
          *output = 1;
          *count++;
        } else {
          *state = OFF;
          *output = 0;
          *count = *count + 1;
        }
        break;
      }
  }
}

void loop() {

  fsm(&state, &output, &count);
  if (output == 1) {
    digitalWrite(OUTPUT_LED, HIGH);
  } else {
    digitalWrite(OUTPUT_LED, LOW);
  }
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" count: ");
  Serial.print(count);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

  delay(1000);                       // wait for 1 second
}
