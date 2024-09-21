#include <stdio.h>
#include <stdint.h>
#include <string.h>
uint64_t xor_operation(uint64_t left, uint64_t right) {
    return left ^ right;
}
uint64_t feistel_function(uint64_t right, uint64_t subkey) {
    return xor_operation(right, subkey);
}
uint64_t des_round(uint64_t input, uint64_t key) {
    uint32_t left = (input >> 32) & 0xFFFFFFFF;
    uint32_t right = input & 0xFFFFFFFF;
    for (int i = 0; i < 16; i++) {
        uint32_t temp = right;
        right = left ^ feistel_function(right, key);
        left = temp;
    }
    return ((uint64_t)left << 32) | right;
}
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    uint64_t ciphertext = des_round(plaintext, key);
    return ciphertext;
}
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t plaintext = des_round(ciphertext, key);
    return plaintext;
}
int main() {
    uint64_t plaintext = 0x0123456789ABCDEF; 
    uint64_t key = 0x133457799BBCDFF1;      
    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: %016llX\n", ciphertext);
    uint64_t decrypted_text = des_decrypt(ciphertext, key);
    printf("Decrypted Text: %016llX\n", decrypted_text);
    return 0;
}
