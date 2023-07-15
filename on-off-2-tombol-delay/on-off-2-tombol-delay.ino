// lampu on-off dengan 2 tombol model FSM dan delay

#define STATE_INITIAL    100
#define STATE_ON    101
#define STATE_OFF   102
#define SWITCH_PB1 3
#define SWITCH_PB2 2
#define LED_OUTPUT 4
#define PERIOD_MS 10 // perioda delay dalam milisecond
#define TIMEOUT 10 // TIMEOUT dalam detik
int state = STATE_INITIAL;
int counter = 0;

void setup() {
  int output = 0;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(SWITCH_PB1, INPUT_PULLUP);
  pinMode(SWITCH_PB2, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println(__FILE__);
  fsm_output(output);
}

void loop() {
  mainloop();
  delay(PERIOD_MS);
}

void fsm(int  *state, int *out, int pb1, int pb2, int *counter) {
  switch (*state) {
    case STATE_INITIAL: { // initial state
        *state = STATE_OFF;
        *out = 0;
        break;
      }
    case STATE_ON: {
        if (pb2 == 0) {
          // tetap
          if (*counter >= TIMEOUT * 1000 / PERIOD_MS) {
            *state = STATE_OFF;
            *out = 0;
          } else {
            *counter = *counter + 1; // tunggu timeout
            *state = STATE_ON;
            *out = 1;
          }
        } else {
          *state = STATE_OFF;
          *out = 0;
        }
        break;
      }
    case STATE_OFF: {
        if (pb1 == 0) {
          // tetap
          *state = STATE_OFF;
          *out = 0;
        } else {
          *counter = 0;
          *state = STATE_ON;
          *out = 1;
        }
        break;
      }
  }
}

void fsm_output(int output_value) {
  if (output_value == 1) {
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    digitalWrite(LED_OUTPUT, LOW);
  }
}

void mainloop(void)
{
  int output = 0;
  int pb1, pb2, switch1, switch2;
  switch1 = digitalRead(SWITCH_PB1);
  switch2 = digitalRead(SWITCH_PB2);
  if (switch1 == 1)
    pb1 = 0;
  else {
    pb1 = 1;
  }
  if (switch2 == 1)
    pb2 = 0;
  else {
    pb2 = 1;
  }
  fsm(&state, &output, pb1, pb2, &counter);
  fsm_output(output);


  // cetak jika ada perubahan state , atau sudah 1 detik berlalu
  static int prev_state = 0;
  static int display_counter = 0;

  if (prev_state != state || display_counter > 1000 / PERIOD_MS) {
    Serial.print("state: ");
    if (state == STATE_ON) {
      Serial.print("ON  ");
    } else if (state == STATE_OFF) {
      Serial.print("OFF ");
    } else {
      Serial.print(state);
    }

    Serial.print(" pb1: ");
    Serial.print(pb1);
    Serial.print(" pb2: ");
    Serial.print(pb2);
    Serial.print(" c: ");
    Serial.print( counter);
    Serial.print(" out: ");
    Serial.print(output);
    Serial.println();
    prev_state = state;
    display_counter = 0;
  }
  display_counter++;

}
