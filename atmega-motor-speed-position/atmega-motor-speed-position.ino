/*
   mengukur posisi dan kecepatan sesaat

  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  library timer:
     - https://github.com/PaulStoffregen/TimerOne
  interkoneksi:
  hijau -> D2
  putih -> D3
  hitam -> GND
  merah -> +5 volt , namun terukur 4 volt


*/
#include <TimerOne.h>   //

#define ENCODER_A 2 // hijau
#define ENCODER_B 3 // putih

int  waktu = 0;
int  posisi = 0;
volatile int counter_kecepatan = 0;

bool pin_A_prev; // status pin 2 sebelumnya
bool pin_B_prev; // status pin 3 sebelumnya

volatile int counter = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), ISR_pin_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), ISR_pin_B, CHANGE);
  Timer1.initialize( 10000 );           //period in microseconds
  Timer1.attachInterrupt( HitungKecepatan );   //attach the Timer1 interrupt
}

void HitungKecepatan() {
  Serial.println(counter_kecepatan);
  counter_kecepatan = 0;
}

void ISR_pin_A() { 
  counter_kecepatan ++;
}

void ISR_pin_B() { 
  counter_kecepatan ++;
}

// the loop function runs over and over again forever
void loop() {
  // lampu kedip hanya untuk menunjukkan sistem tidak hang
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
