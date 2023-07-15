//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//
#include <MCP3XXX.h>
#include <driver/dac.h>
hw_timer_t *My_timer = NULL;
int value = 0;
MCP3008 adc;
int counter = 0, last_time = 0, current_time = 0, durasi = 0;
volatile int work_flag = 0;

void IRAM_ATTR onTimer() {
  digitalWrite(21, HIGH);  // turn the LED on (HIGH is the voltage level)
  work_flag = 1;           // tandai semaphore untuk melakukan proses filter digital
  digitalWrite(21, LOW);   // turn the LED on (HIGH is the voltage level)
}

void setup() {

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("start");
  adc.begin();
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  Serial.println("DAC init");
  dac_output_enable(DAC_CHANNEL_1);  // nyalakan DAC channel 1 (pin 25)
  Serial.println("init filter");
  filter_init();
  Serial.println("start SPI");
  adc.spistart();
  Serial.println("start timer");
  My_timer = timerBegin(0, 80, true);  //  hardware timer 0, prescaler, count up
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 50, true);  // delay (us) // 20 kHz
  timerAlarmEnable(My_timer);           //Just Enable
  Serial.println("start loops");
}

void loop() {
  float input = 0;
  float output = 0;
  int output_int;
  for (;;) {
    if (work_flag == 1) {
      digitalWrite(22, HIGH);  // turn the LED on (HIGH is the voltage level)
      input = adc.analogRead(0);
      input = input / 1024;  // 10 bit normalized
      input = input - 0.5;
      // mestinya di sini ada penguatan input, tergantung nilai min dan max dari input
      output = filter(input);
      output = output + 0.5;  // offset
      output = output * 256;  // scaling to 8 bit DAC
      output_int = output;    // penguatan output
      dac_output_voltage(DAC_CHANNEL_1, output_int);
      digitalWrite(22, LOW);  // turn the LED on (HIGH is the voltage level)
      work_flag = 0;
    } else {
    }
  }
}

// implementasi filter digital
#define ORDE_FILTER 53
float buffer[ORDE_FILTER + 1];
float y_history[ORDE_FILTER + 1];

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