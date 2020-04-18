/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: waskita
 *
 * Created on April 18, 2020, 4:39 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "string.h"

/**
 * Filter Moving Average sederhana, untuk demo
 * @param input
 * @return 
 */
float filter_moving_average(float input[3]) {
    return (input[0] + input[1] + input[2]) / 3;
}

#define BUFFER_LENGTH 100

/*
 * 
 */
int main(int argc, char** argv) {
    char output_filename[] = "simulasi-filter.csv";
    float delay_line[3];
    // inisialisasi delay line
    delay_line[0] = 0;
    delay_line[1] = 0;
    delay_line[2] = 0;
    char data[BUFFER_LENGTH];
    char filename[] = "../anti-aliasing-out.csv";
    FILE *fp;
    FILE *output_fp;
    output_fp = fopen(output_filename, "w"); // file output
    fprintf(output_fp, "n,vin,lpf_out,filter_out\n");
    fp = fopen(filename, "r");
    if (fp != NULL && output_fp != NULL) { // kedua file harus dapat dibuka
        printf("read file %s ok\n", filename);
        fgets(data, BUFFER_LENGTH, fp); // buang baris pertama, karena isinya nama kolom
        while (fgets(data, BUFFER_LENGTH, fp) != NULL) {
            float output; // output filter sesaat
            int kolom = 0; // menandai angka itu di kolom berapa
            printf("%s\n", data);
            int angka_waktu, angka_input, angka_output_lpf;

            int init_size = strlen(data);
            char delim[] = ",";

            char *ptr = strtok(data, delim);

            while (ptr != NULL) {
                int angka = 0;
                printf("%s\n", ptr);
                angka = atoi(ptr);
                printf("angka %d\n", angka);
                ptr = strtok(NULL, delim);
                if (kolom == 0) {
                    angka_waktu = angka;
                }
                if (kolom == 1) {
                    angka_input = angka;
                }
                if (kolom == 2) {
                    angka_output_lpf = angka;
                }

                kolom++;
            }
            printf("waktu: %d vin: %d vout:%d\n", angka_waktu, angka_input, angka_output_lpf);

            delay_line[2] = delay_line[1];
            delay_line[1] = delay_line[0];
            delay_line[0] = angka_output_lpf;
            output = filter_moving_average(delay_line); // hitung output filter digital
            printf("output %f\n", output);
            fprintf(output_fp, "%d,%d,%d,%f\n", angka_waktu, angka_input, angka_output_lpf, output);
        }
        fclose(fp);
        fclose(output_fp);

    } else {
        printf("error read file %s\n", filename);
    }
    return (EXIT_SUCCESS);
}

// ref: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split