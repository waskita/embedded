/*
  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/
*/

#define ENCODER_A PA0 // hijau
#define ENCODER_B PA1 // putih
#define LED_BUILTIN 22 // LOLIN32 LITE

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), ISR_pin_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), ISR_pin_B, CHANGE);
}

int  waktu = 0;
volatile int  posisi = 0;
char pin_A_prev; // status pin 2 sebelumnya
char pin_B_prev; // status pin 3 sebelumnya
//volatile int counter = 0;

signed int DecodeRotary(char pin_A, char pin_A_prev, char pin_B, char pin_B_prev) {
  if (pin_A == 0 && pin_A_prev == 0 && pin_B == 0 && pin_B_prev == 1) {
    return -1;
  }
  if (pin_A == 0 && pin_A_prev == 0 && pin_B == 1 && pin_B_prev == 0) {
    return 1;
  }
  if (pin_A == 0 && pin_A_prev == 1 && pin_B == 0 && pin_B_prev == 0) {
    return 1;
  }
  if (pin_A == 0 && pin_A_prev == 1 && pin_B == 1 && pin_B_prev == 1) {
    return -1;
  }

  if (pin_A == 1 && pin_A_prev == 0 && pin_B == 0 && pin_B_prev == 0) {
    return -1;
  }
  if (pin_A == 1 && pin_A_prev == 0 && pin_B == 1 && pin_B_prev == 1) {
    return 1;
  }
  if (pin_A == 1 && pin_A_prev == 1 && pin_B == 0 && pin_B_prev == 1) {
    return 1;
  }
  if (pin_A == 1 && pin_A_prev == 1 && pin_B == 1 && pin_B_prev == 0) {
    return -1;
  }
  return 0;
}
void ISR_pin_A() {
  int  delta;
  bool  pin_A, pin_B;
  pin_A = digitalRead(ENCODER_A);
  pin_B = digitalRead(ENCODER_B);

  delta = DecodeRotary(pin_A, pin_A_prev, pin_B, pin_B_prev);
  posisi += delta;
  //  Serial.println(delta);

  pin_A_prev = pin_A;
  pin_B_prev = pin_B;
}

void ISR_pin_B() {
  int  delta;
  char  pin_A, pin_B;
  pin_A = digitalRead(ENCODER_A);
  pin_B = digitalRead(ENCODER_B);

  delta = DecodeRotary(pin_A, pin_A_prev, pin_B, pin_B_prev);
  posisi += delta;
  //  Serial.println(delta);
  pin_A_prev =  pin_A;
  pin_B_prev = pin_B;
}

// the loop function runs over and over again forever
void loop() {
  waktu++;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
  Serial.print(waktu);
  Serial.print(" ");
  Serial.println(posisi);
}
