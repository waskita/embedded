// library: https://github.com/bakercp/MCP3XXX
#include <MCP3XXX.h>
MCP3008 adc;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  // Use the default SPI hardware interface.
  adc.begin();
  // Or use custom pins to use a software SPI interface.
  // adc.begin(SS, MOSI, MISO, SCK);
  pinMode(22, OUTPUT); // digital output for monitoring
  pinMode(21, OUTPUT);
}
int counter = 0, last_time = 0, current_time = 0;
float durasi=0;
int jumlah_iterasi=100000;

void loop() {
  for (;;) {

    digitalWrite(22, HIGH);  // turn the LED on (HIGH is the voltage level)
    adc.analogRead(0);
    digitalWrite(22, LOW);  // turn the LED on (HIGH is the voltage level)

    counter = counter + 1;
    if (counter == jumlah_iterasi) {  // tiap 10000x berhenti
      counter = 0;
      current_time = millis();
      durasi = (float)(current_time - last_time) / (float) jumlah_iterasi;
      Serial.print("durasi (ms) ");
      Serial.println(durasi,4);
      last_time = current_time;
    }
  }
}