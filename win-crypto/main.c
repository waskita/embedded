// sumber: https://everythingesp.com/esp32-arduino-tutorial-encryption-aes128-in-ecb-mode/
/*
 * enkripsi data dengan AES-CBC
 * modifikasi dari https://everythingesp.com/esp32-arduino-tutorial-encryption-aes128-in-ecb-mode/
 * menggunakan library mbedtls dari cygwin
 */
#include "mbedtls/aes.h"
#include "string.h"
#include "stdio.h"

void encrypt(char * plainText, char * key, unsigned char * outputBuffer) {

    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, (const unsigned char*) key, strlen(key) * 8);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*) plainText, outputBuffer);
    mbedtls_aes_free(&aes);
}

void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer) {

    mbedtls_aes_context aes;

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, (const unsigned char*) key, strlen(key) * 8);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*) chipherText, outputBuffer);
    mbedtls_aes_free(&aes);
}

int main(void) {
    char * key = "abcdefghijklmnop";

    char *plainText = "Tech tutorials x";
    unsigned char cipherTextOutput[16];
    unsigned char decipheredTextOutput[16];

    encrypt(plainText, key, cipherTextOutput);
    decrypt(cipherTextOutput, key, decipheredTextOutput);

    printf("Original plain text: %s\n", plainText);

    printf("Ciphered text:\n");
    for (int i = 0; i < 16; i++) {

        char str[3];

        sprintf(str, "%02x", (int) cipherTextOutput[i]);
        printf("%s", str);
    }

    printf("\n\nDeciphered text:\n");
    for (int i = 0; i < 16; i++) {
        printf("%c", (char) decipheredTextOutput[i]);
        //printf("%c", (char) decipheredTextOutput[i]);
    }
    return 0;
}