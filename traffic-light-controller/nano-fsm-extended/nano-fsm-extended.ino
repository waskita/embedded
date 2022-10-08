// implementasi traffic light controller di buku Lee & Seshia Example 3.9

#define STATE_RED    100
#define STATE_GREEN   101
#define STATE_PENDING   102
#define STATE_YELLOW   103
#define PEDESTRIAN_BUTTON 11

#define OUTPUT_RED     2
#define OUTPUT_GREEN   3
#define OUTPUT_YELLOW  4

int state ;
int sig_r = 0;
int sig_g = 0;
int sig_y = 0;
int count = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(OUTPUT_RED, OUTPUT);
  pinMode(OUTPUT_GREEN, OUTPUT);
  pinMode(OUTPUT_YELLOW, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PEDESTRIAN_BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println(__FILE__);
  fsm_init();
  activate_output(sig_r, sig_g, sig_y);
  print_state(0);
  delay(1000);
}

// int output_r, output_g, output_y;

// activate red/green/yellow light depends on sigR,sigG,sigY
void activate_output(int r, int g, int y) {
  if (r == 1) { // turn on RED light
    digitalWrite(OUTPUT_RED, HIGH);
    digitalWrite(OUTPUT_GREEN, LOW);
    digitalWrite(OUTPUT_YELLOW, LOW);
  }
  if (g == 1) { // turn on GREEN light
    digitalWrite(OUTPUT_RED, LOW);
    digitalWrite(OUTPUT_GREEN, HIGH);
    digitalWrite(OUTPUT_YELLOW, LOW);
  }

  if (y == 1) { // turn on YELLOW light
    digitalWrite(OUTPUT_RED, LOW);
    digitalWrite(OUTPUT_GREEN, LOW);
    digitalWrite(OUTPUT_YELLOW, HIGH);
  }
}

void fsm_init() {
  state = STATE_RED;
  count = 0;
  sig_r=1; // initially, red light on
}

void fsm(int  *state, int *sig_r, int *sig_g, int *sig_y, int *count, int pedestrian) {
  *sig_r = 0; // default output adalah 0
  *sig_g = 0; // default output adalah 0
  *sig_y = 0; // default output adalah 0
  switch (*state) {
    case STATE_RED: {
        if (*count >= 60) {
          *state = STATE_GREEN;
          *sig_g = 1;
          *count = 0;
        } else {
          *count = *count + 1;
        }
        break;
      }
    case STATE_GREEN: {
        if (pedestrian == 1 && *count < 60) {
          *state = STATE_PENDING;
          *count = *count + 1;
        } else if (pedestrian == 1 && *count >= 60) {
          *sig_y = 1;
          *state = STATE_YELLOW;
          *count = 0;
        } else if (pedestrian == 0 && *count < 60) {
          *count = *count + 1;
        } else {
          // do nothing
        }
        break;
      }
    case STATE_PENDING: {
        if (*count >= 60) {
          *state = STATE_YELLOW;
          *sig_y = 1;
          *count = 0;
        } else {
          *count = *count + 1;
        }
        break;
      }
    case STATE_YELLOW: {
        if (*count >= 5) {
          *state = STATE_RED;
          *sig_r = 1;
          *count = 0;
        } else {
          *count = *count + 1;
        }
        break;
      }
  }
}

void print_state(int ped) {
  Serial.print("state: ");
  if (state == STATE_RED) {
    Serial.print("RED    ");
  }
  if (state == STATE_GREEN) {
    Serial.print("GREEN  ");
  }
  if (state == STATE_PENDING) {
    Serial.print("PENDING");
  }
  if (state == STATE_YELLOW) {
    Serial.print("YELLOW ");
  }
  Serial.print(" count: ");
  Serial.print(count);
  Serial.print(" sig r:");
  Serial.print(sig_r);
  Serial.print(" g:");
  Serial.print(sig_g);
  Serial.print(" y:");
  Serial.print(sig_y);
  Serial.print(" ped:");
  Serial.print(ped);
  Serial.println();
}
void loop() {
  int pedestrian = 0;
  int button_input ;
  button_input = digitalRead(PEDESTRIAN_BUTTON); // active low, jadi perlu dibalik
  if (button_input == 1) {
    pedestrian = 0;
  } else {
    pedestrian = 1;
  }
  fsm(&state, &sig_r, &sig_g, &sig_y,  &count, pedestrian);
  activate_output(sig_r, sig_g, sig_y);
  print_state(pedestrian);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW); // LED builtin blinks at around 1 Hz
  delay(500);                       
  digitalWrite(LED_BUILTIN, HIGH);
}
