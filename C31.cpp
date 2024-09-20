#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16
#define Rb_64  0x1B
#define Rb_128 0x87
void print_block(const char *label, const uint8_t *block, size_t size) {
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}
void generate_subkey(uint8_t *subkey, size_t block_size, uint8_t Rb) {
    uint8_t msb = subkey[0] & 0x80; 
    for (size_t i = 0; i < block_size - 1; i++) {
        subkey[i] = (subkey[i] << 1) | (subkey[i + 1] >> 7);
    }
    subkey[block_size - 1] <<= 1;
    if (msb) {
        subkey[block_size - 1] ^= Rb;
    }
}

int main() {
    uint8_t L_64[BLOCK_SIZE_64] = {0};
    uint8_t L_128[BLOCK_SIZE_128] = {0};
    memset(L_64, 0x12, BLOCK_SIZE_64);  
    memset(L_128, 0x34, BLOCK_SIZE_128);
    print_block("L_64", L_64, BLOCK_SIZE_64);
    print_block("L_128", L_128, BLOCK_SIZE_128);
    uint8_t K1_64[BLOCK_SIZE_64];
    uint8_t K2_64[BLOCK_SIZE_64];
    memcpy(K1_64, L_64, BLOCK_SIZE_64);
    generate_subkey(K1_64, BLOCK_SIZE_64, Rb_64);
    memcpy(K2_64, K1_64, BLOCK_SIZE_64);
    generate_subkey(K2_64, BLOCK_SIZE_64, Rb_64);
    uint8_t K1_128[BLOCK_SIZE_128];
    uint8_t K2_128[BLOCK_SIZE_128];
    memcpy(K1_128, L_128, BLOCK_SIZE_128);
    generate_subkey(K1_128, BLOCK_SIZE_128, Rb_128);
    memcpy(K2_128, K1_128, BLOCK_SIZE_128);
    generate_subkey(K2_128, BLOCK_SIZE_128, Rb_128);
    print_block("K1_64", K1_64, BLOCK_SIZE_64);
    print_block("K2_64", K2_64, BLOCK_SIZE_64);
    print_block("K1_128", K1_128, BLOCK_SIZE_128);
    print_block("K2_128", K2_128, BLOCK_SIZE_128);

    return 0;
}