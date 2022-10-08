#include "data.h"

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

/**
   filter digital sederhana, real nya mesti pakai butterworth, chebysev, dan sebagainya sesuai keperluan
*/
float filter_moving_average(float input[3]) {
  return (input[0] + input[1] + input[2]) / 3;
}

void loop() {
  float delay_line[3]; // jumlah delay line sesuai orde filter
  float data = 0;
  float output;
  // pengukuran waktu
  unsigned long waktu_awal = millis();
  unsigned long y = 0;
  data = 1.0;
  Serial.println("start");
  for (y = 0; y < 1000000L; y++) {
    data = data + 1.0; // data mesti diubah terus, supaya tidak dioptimize oleh compiler
    data = (data+ output)/2; // supaya output tidak dioptimize
    delay_line[2] = delay_line[1];
    delay_line[1] = delay_line[0];
    delay_line[0] = data;
    output = filter_moving_average(delay_line);
  }
  unsigned long waktu_akhir = millis();
  Serial.println(output); // output mesti dipakai, supaya tidak dioptimize oleh compiler
  Serial.print("waktu awal:");
  Serial.println(waktu_awal);
  Serial.print("waktu akhir:");
  Serial.println(waktu_akhir);
  Serial.print("beda waktu:");
  Serial.println(waktu_akhir - waktu_akhir);


  while (1) {
    // halt di sini
  }
}
