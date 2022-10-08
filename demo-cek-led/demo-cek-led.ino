// menguji apakah semua lampu dapat dinyalakan dan dimatikan.

#define LED_1_A 7
#define LED_1_B 6
#define LED_2_A 5
#define LED_2_B 4
#define LED_3_A 3
#define LED_3_B 2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_1_A, OUTPUT);
  pinMode(LED_1_B, OUTPUT);
  pinMode(LED_2_A, OUTPUT);
  pinMode(LED_2_B, OUTPUT);
  pinMode(LED_3_A, OUTPUT);
  pinMode(LED_3_B, OUTPUT);
}
// the loop function runs over and over again forever
void loop() {

  digitalWrite(LED_1_A, HIGH);
  digitalWrite(LED_1_B, HIGH);
  digitalWrite(LED_2_A, HIGH);
  digitalWrite(LED_2_B, HIGH);
  digitalWrite(LED_3_A, HIGH);
  digitalWrite(LED_3_B, HIGH);

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_1_A, LOW);
  digitalWrite(LED_1_B, LOW);
  digitalWrite(LED_2_A, LOW);
  digitalWrite(LED_2_B, LOW);
  digitalWrite(LED_3_A, LOW);
  digitalWrite(LED_3_B, LOW);

  delay(1000);                       // wait for a second
}
