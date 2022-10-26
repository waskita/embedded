// lampu kedip 1 Hz dengan model FSM dan timer one
// https://www.arduino.cc/reference/en/libraries/timerone/
// To install, cari library timerone dari Sketch -> Include Library -> Manage Libraries

#include <TimerOne.h>
#define ON    100
#define OFF   101
#define SWITCH_CLOSE 3
#define SWITCH_OPEN 2
#define LED_OUTPUT 4
int state = OFF;

void setup() {
  int output = 0;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(SWITCH_CLOSE, INPUT_PULLUP);
  pinMode(SWITCH_OPEN, INPUT_PULLUP);

  Serial.begin(115200);
  fsm_init(&state, &output);
  fsm_output(output);
  Timer1.initialize(1000000); // delay dalam microsecond , total 10 ms
  Timer1.attachInterrupt(ISR_Timer1);
}

void loop() {
}

void fsm_init(int *state, int *out) {
  *state = OFF;
  *out = 0;
}
void fsm(int  *state, int *out, int switch_close, int switch_open) {
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

void state_print(int state, int output) {
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.println();

}
void ISR_Timer1(void) // dipanggil setiap kali ada timer interrupt
{
  int output = 0;
  int switch_close_read;
  int switch_close;
  int switch_open_read;
  int switch_open;
  switch_close_read = digitalRead(SWITCH_CLOSE);
  if (switch_close_read == 0) {
    switch_close = 1;
  }
  switch_open_read = digitalRead(SWITCH_OPEN);
  if (switch_open_read == 0) {
    switch_open = 1;
  }

  fsm(&state, &output, switch_close, switch_open);
  fsm_output(output);
  state_print(state, output);
}
