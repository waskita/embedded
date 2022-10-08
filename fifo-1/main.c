/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: waskita
 *
 * Created on November 10, 2019, 2:41 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define FIFO_LENGTH 20
typedef int fifodata;

typedef struct fifo_simple {
    int head; // tempat menulis data baru
    int tail; // tempat mengambil data lama
    int num_element; // jumlah byte di dalam
    fifodata data[FIFO_LENGTH];
} fifo_simple;

struct fifo_simple fs;

void fifo_simple_init(fifo_simple *fs) {
    fs->head = 0;
    fs->num_element = 0;
    fs->tail = 0;
}

/**
 * Masukkan data ke dalam FIFO
 * @param fs struktur data FIFO
 * @param data data yang dimasukkan
 * @return 0 jika tidak berhasil, 1 jika tidak berhasil
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
 * Keluarkan data dari FIFO
 * @param fs
 * @param data
 * @return 0 jika tidak ada, 1 jika ada
 */
int fifo_get(fifo_simple *fs, fifodata * data) {
    // ambil 1 data kalau ada
    if (fs->num_element > 0) {
        fs->num_element--;
        *data = fs->data[fs->tail];
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

/*
 * 
 */
int main(int argc, char** argv) {
    fifo_simple_init(&fs);
    fifo_print_status(&fs);
    fifo_put(&fs, 100);
    fifo_put(&fs, 101);
    fifo_put(&fs, 102);
    fifo_put(&fs, 103);
    fifo_put(&fs, 104);
    fifo_put(&fs, 105);
    fifo_put(&fs, 106);
    fifo_put(&fs, 107);
    fifo_put(&fs, 108);
    fifo_put(&fs, 109);
    fifo_put(&fs, 110);

    fifo_put(&fs, 111);
    fifo_put(&fs, 112);
    fifo_put(&fs, 113);
    fifo_put(&fs, 114);
    fifo_put(&fs, 115);
    fifo_put(&fs, 116);
    fifo_put(&fs, 117);
    fifo_put(&fs, 118);
    fifo_put(&fs, 119);

    fifo_put(&fs, 120);
    fifo_put(&fs, 200);
    fifo_put(&fs, 255);

    fifo_print_status(&fs);

    fifodata buffer;

    fifo_get(&fs, &buffer);
    fifo_print_status(&fs);

    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_get(&fs, &buffer);
    fifo_print_status(&fs);

    return (EXIT_SUCCESS);
}

