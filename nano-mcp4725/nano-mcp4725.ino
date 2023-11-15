// idea from https://learn.sparkfun.com/tutorials/mcp4725-digital-to-analog-converter-hookup-guide/all
#define MCP4725_ADDR 0x60
#include <Wire.h>  //Include the Wire library to talk I2C

int counter;  // how many iterations
int time_begin = 0;
int time_end = 0;
int duration;
void setup() {
  Wire.begin();
  //  Wire.setClock(100000);
  Wire.setClock(400000); // https://www.arduino.cc/reference/en/language/functions/communication/wire/setclock/
  Serial.begin(115200);
  counter = 0;
  Serial.println("start benchmark");
}
//---------------------------------------------------
void loop() {
  int value;  // angka yang ditulis
  value = 0;  // minimum value
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                 // cmd to update the DAC
  Wire.write(value >> 4);         // the 8 most significant bits...
  Wire.write((value & 15) << 4);  // the 4 least significant bits...
  Wire.endTransmission();

  value = 4095;  // maximum value
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                 // cmd to update the DAC
  Wire.write(value >> 4);         // the 8 most significant bits...
  Wire.write((value & 15) << 4);  // the 4 least significant bits...
  Wire.endTransmission();

  counter = counter + 1;
  if (counter >= 10000) {
    float period;
    int time_now = millis();
    counter = 0;
    duration = time_now - time_begin;
    period = duration / 10000.0 / 2.0;
    Serial.print("period (ms): ");
    Serial.println(period);
    //  prepare next round
    time_begin = time_now;
  }
}
