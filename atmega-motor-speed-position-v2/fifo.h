/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

/*
   File:   fifo.h
   Author: waskita

   Created on December 11, 2019, 7:14 AM
*/

#ifndef FIFO_H
#define FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#define FIFO_LENGTH 1000

typedef struct fifodata {
  float temperature;
  float humidity;
  float pressure;
  float pH;
  int ph_temperature;
  int ph_measuring_potential;
  int sequence_number;
  int sample_time; // timestamp
  
} fifodata;

typedef struct fifo_simple {
  int head; // tempat menulis data baru
  int tail; // tempat mengambil data lama
  int num_element; // jumlah byte di dalam
  fifodata data[FIFO_LENGTH];
} fifo_simple;

void fifo_simple_init(fifo_simple *fs);
int fifo_put(fifo_simple *fs, fifodata data);
int fifo_get(fifo_simple *fs, fifodata * data);
void fifo_print_status(fifo_simple *fs);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_H */
