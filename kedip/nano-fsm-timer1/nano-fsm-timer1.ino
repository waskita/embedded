// lampu kedip 1 Hz dengan model FSM dan timer one
// https://www.arduino.cc/reference/en/libraries/timerone/
// To install, cari library timerone dari Sketch -> Include Library -> Manage Libraries

#include <TimerOne.h>
#define ON    100
#define OFF   101
#define LED_OUTPUT 3
int state = OFF;

void setup() {
  int output = 0;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  Serial.begin(115200);
  fsm_init(&state,&output);
  fsm_output(output);
  Timer1.initialize(1000000); // delay dalam microsecond
  Timer1.attachInterrupt(ISR_Timer1);
}

void loop() {
}

void fsm_init(int *state, int *out) {
  *state = OFF;
  *out = 0;
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

void fsm_output(int output_value) {
  if (output_value == 1) {
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    digitalWrite(LED_OUTPUT, LOW);
  }
}

void ISR_Timer1(void)
{
  int output = 0;
  fsm(&state, &output);
  fsm_output(output);
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();
}
