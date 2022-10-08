/*
 * pengujian potensiometer dengan ATmega328 
 * tegangan dari potensiometer dibaca setiap 10 ms
 * interrupt Timer1 menggunakan library TimerOne 
 * - (https://playground.arduino.cc/Code/Timer1/)
 * - https://github.com/PaulStoffregen/TimerOne
 * Output dari port serial dibaca menggunakan RealTerm (https://sourceforge.net/projects/realterm/)
 * 
 */
#include <TimerOne.h>   //

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

int counter = 0;
void ScanADC()
{
  counter++;
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  Timer1.initialize( 10000 );           //period in microseconds 
  Timer1.attachInterrupt( ScanADC );   //attach the Timer1 interrupt 
  pinMode(LED_BUILTIN, OUTPUT);
}

int status = 0;
void loop() { // superloop hanya untuk lampu kedip
  if (counter >= 200) {
    counter = counter - 200;
    if (status == 0) {
      status = 1;
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
      status = 0;
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    }
  }

}
