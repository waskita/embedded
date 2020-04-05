/*
  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  software ini hanya menghitung pulsa, tidak menghitung arah gerakan
*/

#define ENCODER_A 2 // hijau
#define ENCODER_B 3 // putih

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

int waktu = 0; // mencatat waktu dengan counter
volatile int counter = 0;

void ISR_pin_A() {
  counter++;
}

void ISR_pin_B() {
  counter++;
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
  Serial.println(counter);
}
