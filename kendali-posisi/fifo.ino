#define FIFO_LENGTH 20

typedef struct fifo_simple {
    int head; // tempat menulis data baru
    int tail; // tempat mengambil data lama
    int num_element; // jumlah byte di dalam
    char data[FIFO_LENGTH];
} fifo_simple;



int fifo_simple_init(struct fifo_simple *fs) {
    fs->head = 0;
    fs->num_element = 0;
    fs->tail = 0;
    return 0;
}

/**
 * Masukkan data ke dalam FIFO
 * @param fs struktur data FIFO
 * @param data data yang dimasukkan
 * @return 0 jika tidak berhasil, 1 jika tidak berhasil
 */
int fifo_put(struct fifo_simple *fs, char data) {
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
int fifo_get(fifo_simple *fs, char  * data) {
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
