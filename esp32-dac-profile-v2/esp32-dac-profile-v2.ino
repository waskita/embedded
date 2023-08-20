// https://github.com/espressif/arduino-esp32/discussions/7889
// https://dronebotworkshop.com/esp32-dac/
// https://deepbluembedded.com/esp32-dac-audio-arduino-examples/
// https://circuitdigest.com/microcontroller-projects/esp32-timers-and-timer-interrupts

#include <driver/dac.h>

int value = 0;

void setup() {
  dac_output_enable(DAC_CHANNEL_1);
}
void loop() {
  for(;;){
    dac_output_voltage(DAC_CHANNEL_1, 0);
    dac_output_voltage(DAC_CHANNEL_1, 255);
  }
}