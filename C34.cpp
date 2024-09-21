#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8 
#define KEY 0xAABBCCDDEEFF0011 
void mock_block_cipher(uint8_t *input, uint8_t *output, uint64_t key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ ((key >> (8 * i)) & 0xFF);
    }
}
void pad(uint8_t *block, size_t *block_size) {
    block[*block_size] = 0x80; 
    for (size_t i = *block_size + 1; i < BLOCK_SIZE; i++) {
        block[i] = 0x00; 
    }
    *block_size = BLOCK_SIZE;
}
void ecb_encrypt(uint8_t *plaintext, size_t len, uint8_t *ciphertext) {
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        mock_block_cipher(&plaintext[i], &ciphertext[i], KEY);
    }
}
void cbc_encrypt(uint8_t *plaintext, size_t len, uint8_t *ciphertext, uint8_t *iv) {
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= previous_block[j]; 
        }
        mock_block_cipher(&plaintext[i], &ciphertext[i], KEY);
        memcpy(previous_block, &ciphertext[i], BLOCK_SIZE); 
    }
}
void cfb_encrypt(uint8_t *plaintext, size_t len, uint8_t *ciphertext, uint8_t *iv) {
    uint8_t feedback_block[BLOCK_SIZE];
    memcpy(feedback_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        uint8_t encrypted_feedback[BLOCK_SIZE];
        mock_block_cipher(feedback_block, encrypted_feedback, KEY);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ encrypted_feedback[j]; 
            feedback_block[j] = ciphertext[i + j]; 
        }
    }
}

int main() {
    uint8_t plaintext[] = "This is a secret message.";
    size_t len = strlen((char *)plaintext);
    size_t padded_len = len;
    if (len % BLOCK_SIZE != 0) {
        padded_len = len + (BLOCK_SIZE - (len % BLOCK_SIZE));
        pad(plaintext, &len);
    }
    uint8_t ecb_ciphertext[padded_len];
    uint8_t cbc_ciphertext[padded_len];
    uint8_t cfb_ciphertext[padded_len];
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    ecb_encrypt(plaintext, padded_len, ecb_ciphertext);
    printf("ECB Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02X", ecb_ciphertext[i]);
    }
    printf("\n");
    cbc_encrypt(plaintext, padded_len, cbc_ciphertext, iv);
    printf("CBC Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02X", cbc_ciphertext[i]);
    }
    printf("\n");
    cfb_encrypt(plaintext, padded_len, cfb_ciphertext, iv);
    printf("CFB Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02X", cfb_ciphertext[i]);
    }
    printf("\n");
    return 0;
}
