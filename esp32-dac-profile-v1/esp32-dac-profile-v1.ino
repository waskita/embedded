#define DAC1 25

void setup() {
  Serial.begin(115200);
}

void loop() {
  while (1) {
    dacWrite(DAC1, 0);
    dacWrite(DAC1, 4095);
  }
}