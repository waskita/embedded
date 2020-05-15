/* 
 *  profiling sensor detak jantung
 *  
 */

#include <TimerOne.h>   

// These constants won't change. They're used to give names to the pins used:
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
  Timer1.initialize( 1000 );           //period in microseconds 
  Timer1.attachInterrupt( ScanADC );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  pinMode(LED_BUILTIN, OUTPUT);
}

const int counter_delta=1000;
int status = 0;
void loop() { // superloop hanya untuk lampu kedip, untuk indikator
  if (counter >= counter_delta) {
    counter = counter - counter_delta;
    if (status == 0) {
      status = 1;
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
      status = 0;
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    }
  }
}
