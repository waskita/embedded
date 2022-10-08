#include "data.h"

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

/**
   filter digital sederhana
*/
float filter_moving_average(float input[3]) {
  return (input[0] + input[1] + input[2]) / 3;
}

void loop() {
  int counter = 0;  
  float delay_line[3];  // delay line untuk FIR
  float output;
  int i;
  delay_line[0] = 0;
  delay_line[1] = 0;
  delay_line[2] = 0;
  Serial.println("start");
  Serial.println("time,filter_in,filter_out");
  for (i = 0; i < 100; i++) {
    float data = 0;
    data = output_adc[i] / 1024.0;

    Serial.print(counter);
    Serial.print(",");
    Serial.print(data);
    Serial.print(",");
    delay_line[2] = delay_line[1];
    delay_line[1] = delay_line[0];
    delay_line[0] = data;

    output = filter_moving_average(delay_line);
    Serial.print(output);
    Serial.println("");
    counter++;
  }

  while (1) {
    // halt di sini
  }
}
