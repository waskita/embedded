
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Wire.h>

#define I2C_SDA 15
#define I2C_SCL 13

Adafruit_MCP4725 dac;

void setup(void) {
  int address = 0;
  int hasil;
  uint32_t speed = 400000L;
  int status;
  status = Wire.begin(I2C_SDA, I2C_SCL, speed);
  Serial.begin(115200);
  Serial.print("Hello! Wire Init status:");
  Serial.println(status);
  Serial.println(speed);

  address = 0x62;
  dac.begin(address);
  Serial.println("Search I2C");
  SearchI2C();
  Serial.println("benchmark");
}
int start_sawtooth = 0;
int current_time;
int duration;
int time_begin;
int time_now;
uint32_t counter;
void loop(void) {
  dac.setVoltage(0, false);
  dac.setVoltage(4095, false);
  counter = counter + 1;
  if (counter >= 10000) {
    float period;
    int time_now = millis();
    counter = 0;
    duration = time_now - time_begin;
    period = duration / 10000.0 / 2;
    Serial.print("period (ms): ");
    Serial.println(period);
    //  prepare next round
    time_begin = time_now;
  }
}

void SearchI2C() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    //    Serial.println(address, HEX);
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}