//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <MCP3XXX.h>


#include <driver/dac.h>


MCP3008 adc;


void setup() {

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("start");
  // Use the default SPI hardware interface.
  adc.begin();
  // Or use custom pins to use a software SPI interface.
  // adc.begin(SS, MOSI, MISO, SCK);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  Serial.println("DAC init");
  dac_output_enable(DAC_CHANNEL_1);  // nyalakan DAC channel 1 (pin 25)
  Serial.println("init filter");
  filter_init();
//  Serial.println("start SPI");
  adc.spistart();
  Serial.println("start loops");
}
int counter = 0, last_time = 0, current_time = 0, durasi = 0;
void loop() {
  float input = 0;
  float output = 0;
  for (;;) {
    int output_int;
    digitalWrite(22, HIGH);  // turn the LED on (HIGH is the voltage level)
    input = adc.analogRead(0);
    input = input / 1024;  // 10 bit normalized
    input = input - 0.5;
    //    Serial.print(input);    // debugging output ADC
    //Serial.print(" ");      // debugging output ADC
    digitalWrite(22, LOW);  // turn the LED on (HIGH is the voltage level)
    // mestinya di sini ada penguatan input, tergantung nilai min dan max dari input
    output = filter(input);
    //Serial.print(output);        // debugging output ADC
    //Serial.print(" ");           // debugging output ADC
    output = output + 0.5;  // offset
    output = output * 256;  // scaling to 8 bit DAC
    output_int = output;    // penguatan output
    //Serial.println(output_int);  // debugging output ADC
    dac_output_voltage(DAC_CHANNEL_1, output_int);
    //     counter = counter + 1;
    if (counter == 10000) {  // tiap 10000x berhenti
      counter = 0;
      current_time = millis();
      durasi = current_time - last_time;
      Serial.print("durasi ");
      Serial.println(durasi);
      last_time = current_time;
    }
  }
}

// implementasi filter digital
#define ORDE_FILTER 53
float buffer[ORDE_FILTER];
float y_history[ORDE_FILTER];

void filter_init() {
  int i;
  for (i = 0; i < ORDE_FILTER; i++) {
    y_history[i] = 0;
  }
}
float filter(float x) {
  int i, j, k;
  int orde_filter = ORDE_FILTER;
  float filter_coefficients[] = { -4.29317419e-20, -4.18549678e-21, -1.79819385e-05, -8.38178513e-05,
                                  -2.28616892e-04, -4.79528638e-04, -8.51847897e-04, -1.33864303e-03,
                                  -1.89910369e-03, -2.44776137e-03, -2.84740649e-03, -2.90866942e-03,
                                  -2.39870072e-03, -1.06016948e-03, 1.35995551e-03, 5.07437980e-03,
                                  1.02166209e-02, 1.68050560e-02, 2.47160945e-02, 3.36720917e-02,
                                  4.32479500e-02, 5.28978134e-02, 6.20002342e-02, 6.99171799e-02,
                                  7.60597872e-02, 7.99523091e-02, 8.12855501e-02, 7.99523091e-02,
                                  7.60597872e-02, 6.99171799e-02, 6.20002342e-02, 5.28978134e-02,
                                  4.32479500e-02, 3.36720917e-02, 2.47160945e-02, 1.68050560e-02,
                                  1.02166209e-02, 5.07437980e-03, 1.35995551e-03, -1.06016948e-03,
                                  -2.39870072e-03, -2.90866942e-03, -2.84740649e-03, -2.44776137e-03,
                                  -1.89910369e-03, -1.33864303e-03, -8.51847897e-04, -4.79528638e-04,
                                  -2.28616892e-04, -8.38178513e-05, -1.79819385e-05, -4.18549678e-21,
                                  -4.29317419e-20 };
  float t;

  int buffer_index = 0;

  //  t = (float)i / (float)20000;  //  time axis

  // hitung history signal
  for (j = orde_filter - 1; j >= 1; j--) {
    int src = j - 1;
    int dst = j;
    y_history[dst] = y_history[src];
    //            printf("%d %d\n",src,dst);
  }
  y_history[0] = x;

  // hitung konvolusi
  float y_out = 0;
  for (k = 0; k < orde_filter; k++) {
    y_out = y_out + y_history[k] * filter_coefficients[k];
  }
  //        fprintf(fp,"\n");
  //    Serial.print(".");
  buffer[buffer_index] = y_out;
  buffer_index++;
  if (buffer_index > 100) {
    buffer_index = 0;
  }
  return y_out;
}