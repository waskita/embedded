
#define OFF_STABLE 100
#define OFF_AWAL 101
#define ON_AWAL 102
#define ON_STABLE 103
#define ON_END  104
#define BATAS_WAKTU 100

#define OUTPUT_LED 3
#define INPUT_SWITCH 12

int state;
int count = 0;
int output = 1;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(OUTPUT_LED, OUTPUT);
  pinMode(INPUT_SWITCH, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println(__FILE__);

  fsm_init(&state, &output, &count);
  delay(1000);
}

void fsm_init(int  *state, int *output, int *count) {
  *state = OFF_STABLE;
  *output = 0;
  *count = 0;
}
void fsm(int  *state, int *output, int *counter, int input) {
  switch (*state) {
    case OFF_AWAL:
      {
        if (input == 0) {
          *state = OFF_STABLE;
          *output = 0;
        } else {
          *state = OFF_AWAL;
          *output = 0;
        }
        break;
      }
    case OFF_STABLE:
      {
        if (input == 1) {
          *state = ON_AWAL;
          *output = 1;
        } else {
          *output = 0;
        }
        break;
      }
    case ON_AWAL:
      {
        if (input == 0) {
          *state = ON_STABLE;
          *output = 1;
        } else {

        }
        break;
      }
    case ON_STABLE:
      {
        if (input == 1) {
          *state = ON_END;
          *output = 1;
          *counter = 0;
        }
        break;
      }
    case ON_END:
      {
        if (input == 0) {
          *state = ON_STABLE;
          *output = 1;
        } else {
          *state = ON_END;
          *counter=*counter+1;
          Serial.println(BATAS_WAKTU);
          Serial.println(*counter);
          if (*counter >= BATAS_WAKTU) {
            *state = OFF_AWAL;
            *output = 0;
          }
        }
        break;
      }
    default:
      {
        *state = OFF_AWAL;
      }
  }
}

void state_print(int state, int count, int input, int output) {
  Serial.print("state: ");
  switch (state) {
    case OFF_STABLE:
      Serial.print("OFF_STABLE");
      break;
    case OFF_AWAL:
      Serial.print("OFF_AWAL  ");
      break;
    case ON_AWAL:
      Serial.print("ON_AWAL   ");
      break;
    case ON_STABLE:
      Serial.print("ON_STABLE ");
      break;
    case ON_END:
      Serial.print("ON_END    ");
      break;
    default:
      Serial.print("UNKNOWN   ");
      break;
  }

  Serial.print(" count: ");
  Serial.print(count);
  Serial.print(" output: ");
  Serial.print( output);
  Serial.print(" input: ");
  Serial.print( input);
  Serial.println();
}
void loop() {
  int input;
  if ( digitalRead(INPUT_SWITCH) == 1) {
    input = 0;
  } else {
    input = 1;
  }

  fsm(&state, &output, &count, input);
  if (output == 1) {
    digitalWrite(OUTPUT_LED, HIGH);
  } else {
    digitalWrite(OUTPUT_LED, LOW);
  }
  state_print(state, count, input, output);
  delay(10);                       // wait for 1 second
}
