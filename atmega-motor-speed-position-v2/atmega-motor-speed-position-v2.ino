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

volatile int  counter_kecepatan = 0;
volatile int  kecepatan_buffer_data = 0; //tempat data
volatile char  kecepatan_buffer_status = 0; // 0= kosong, 1=berisi

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(115200);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), ISR_pin_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), ISR_pin_B, CHANGE);
  Timer1.initialize( 10000 );           //period in microseconds
  Timer1.attachInterrupt( HitungKecepatan );   //attach the Timer1 interrupt
}

void HitungKecepatan() {
  //  cli();//disable interrupt
  //  D12 = PB4
  //  digitalWrite(12, HIGH);
  kecepatan_buffer_data = counter_kecepatan;
  kecepatan_buffer_status = 1; // tandai bahwa ada data di sini
  counter_kecepatan = 0;
  //  digitalWrite(12, LOW);
  //  sei();//enable interrupt
}

void ISR_pin_A() {
  //  PORTB |= 1 << 4;
  counter_kecepatan ++;
  //  PORTB &= ~(1 << 4);
}

void ISR_pin_B() {
  //  PORTB |= 1 << 2;
  counter_kecepatan ++;
  //  PORTB &= ~(1 << 2);
}

int max_speed = 0;

void loop() {
  int kecepatan_tmp;
  cli();//disable interrupt
  if (kecepatan_buffer_status == 1) {
    kecepatan_tmp = kecepatan_buffer_data;
    kecepatan_buffer_status = 0; // FIFO kosong, siap menerima data
    sei();//enable interrupt
    //    digitalWrite(LED_BUILTIN, HIGH);
    //    PORTB |= 1 << 2;
    //    if (kecepatan_tmp > max_speed) {
    max_speed = kecepatan_tmp;
    Serial.println(kecepatan_tmp);
    //}

    //PORTB &= ~(1 << 2);
    //    digitalWrite(LED_BUILTIN, LOW);
  } else {
    sei();//enable interrupt
  }

}
