/*
 * membuat datafile untuk simulasi filter digital di Arduino
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
#include "math.h"

#define BUFFER_LENGTH 100

int main(int argc, char** argv) {
    int first_flag = 1;
    char input_filename[] = "../simulasi-filter/simulasi-filter.csv";
    char data_filename[] = "data.h";
    char data[BUFFER_LENGTH];

    FILE *fp;
    FILE *data_fp;

    fp = fopen(input_filename, "r");
    data_fp = fopen(data_filename, "w");

    if (fp != NULL && data_fp != NULL) { // kedua file harus dapat dibuka

        fprintf(data_fp, "const int output_adc[] = {");
        printf("read file %s ok\n", input_filename);
        fgets(data, BUFFER_LENGTH, fp); // buang baris pertama, karena isinya nama kolom
        while (fgets(data, BUFFER_LENGTH, fp) != NULL) {
            float output; // output filter sesaat
            int kolom = 0; // menandai angka itu di kolom berapa
            printf("%s\n", data);
            int angka_waktu; // waktu integer
            float angka_input, angka_output_lpf = 0; // sinyal floating point

            int init_size = strlen(data);
            char delim[] = ",";

            char *ptr = strtok(data, delim);

            while (ptr != NULL) {
                float angka = 0;
                printf("kolom:%d ptr:%s ", kolom, ptr);
                angka = atof(ptr);
                printf("angka %f\n", angka);
                ptr = strtok(NULL, delim);

                if (kolom == 2) {
                    angka_output_lpf = angka;
                    printf("lpf:%f \n", angka_output_lpf);
                }
                kolom++;
            }
            int angka_output_adc;
            angka_output_adc = angka_output_lpf * 1024;
            if (first_flag == 1) { // hanya data pertama saja, tanpa koma
                fprintf(data_fp, "%d\n", angka_output_adc);
                first_flag = 0;
            } else {
                fprintf(data_fp, ",%d\n", angka_output_adc);
            }

        }
        fprintf(data_fp, "};");
        fclose(fp);

    } else {
        printf("error read file %s\n", input_filename);
    }
    return (EXIT_SUCCESS);
}

// ref: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split