#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8
#define TRIPLE_DES_KEY_SIZE 24

// Function prototypes
void desEncryptBlock(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext);
void desDecryptBlock(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext);
void tripleDesEncrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length);
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output);

// Dummy DES encryption and decryption functions
void desEncryptBlock(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    // Dummy encryption - in practice, replace this with the actual DES encryption implementation
    memcpy(ciphertext, plaintext, DES_BLOCK_SIZE);
}

void desDecryptBlock(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    // Dummy decryption - in practice, replace this with the actual DES decryption implementation
    memcpy(plaintext, ciphertext, DES_BLOCK_SIZE);
}

// 3DES CBC mode encryption function
void tripleDesEncrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length) {
    uint8_t block[DES_BLOCK_SIZE];
    uint8_t tempBlock[DES_BLOCK_SIZE];
    uint8_t *currentIv = iv;

    for (size_t i = 0; i < length; i += DES_BLOCK_SIZE) {
        xorBlocks(plaintext + i, currentIv, block);
        desEncryptBlock(block, key, tempBlock);
        desDecryptBlock(tempBlock, key + DES_KEY_SIZE, block);
        desEncryptBlock(block, key + 2 * DES_KEY_SIZE, ciphertext + i);
        currentIv = ciphertext + i;
    }
}

// XOR two blocks
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < DES_BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

int main() {
    uint8_t key[TRIPLE_DES_KEY_SIZE] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67
    };
    uint8_t iv[DES_BLOCK_SIZE] = {
        0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0
    };
    uint8_t plaintext[DES_BLOCK_SIZE * 2] = {
        0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28
    };
    uint8_t ciphertext[DES_BLOCK_SIZE * 2];

    printf("Plaintext:\n");
    for (int i = 0; i < DES_BLOCK_SIZE * 2; i++) {
        printf("%02x ", plaintext[i]);
    }
    printf("\n");

    tripleDesEncrypt(plaintext, key, iv, ciphertext, sizeof(plaintext));

    printf("Ciphertext:\n");
    for (int i = 0; i < DES_BLOCK_SIZE * 2; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}