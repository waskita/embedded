/*
   To change this license header, choose License Headers in Project Properties.
   To change this template file, choose Tools | Templates
   and open the template in the editor.
*/

#include "fifo.h"
#include "stdio.h"

void fifo_simple_init(fifo_simple *fs) {
  fs->head = 0;
  fs->num_element = 0;
  fs->tail = 0;
}

/**
   Masukkan data ke dalam FIFO
   @param fs struktur data FIFO
   @param data data yang dimasukkan
   @return 0 jika tidak berhasil, 1 jika tidak berhasil
*/
int fifo_put(fifo_simple *fs, fifodata data) {
  // tambah 1 data
  if (fs->num_element < FIFO_LENGTH) {
    fs->data[fs->head] = data;
    fs->head++;
    if (fs->head >= FIFO_LENGTH) {
      fs->head = 0;
    }
    fs->num_element++;
    return 1;
  } else {
    return 0;
  }

}

/**
   Keluarkan data dari FIFO
   @param fs
   @param data
   @return 0 jika tidak ada, 1 jika ada
*/
int fifo_get(fifo_simple *fs, fifodata * return_data) {
  // ambil 1 data kalau ada
  if (fs->num_element > 0) {
    fs->num_element--;
    *return_data = fs->data[fs->tail];
    fs->tail++;
    if (fs->tail >= FIFO_LENGTH) {
      fs->tail = 0;
    }
    return 1;
  } else {
    return 0;
  }
}

void fifo_print_status(fifo_simple *fs) {
  printf("alamat struktur    %p\n", fs);
  printf("alamat head        %p\n", &fs->head);
  printf("alamat tail        %p\n", &fs->tail);
  printf("alamat num_element %p\n", &fs->num_element);
  printf("alamat data        %p\n", fs->data);
  printf("alamat data 0      %p\n", &fs->data[0]);
  printf("alamat data 1      %p\n", &fs->data[1]);
  printf("alamat data akhir  %p\n", &fs->data[FIFO_LENGTH - 1]);

  printf("head       : %d\n", fs->head);
  printf("tail       : %d\n", fs->tail);
  printf("num_element: %d\n", fs->num_element);
  for (int i = 0; i < FIFO_LENGTH; i++) {
    printf("%3d ", fs->data[i]);
  }
  printf("\n");
}
