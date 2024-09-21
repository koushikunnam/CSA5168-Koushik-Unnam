#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ALPHABET_SIZE 26
void generate_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE; 
    }
}
void encrypt(char *plaintext, char *ciphertext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}
void decrypt(char *ciphertext, char *decrypted, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decrypted[i] = ((ciphertext[i] - 'A' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decrypted[i] = ((ciphertext[i] - 'a' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[length] = '\0'; 
}
int main() {
    srand(time(NULL)); 
    char plaintext[256];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    size_t length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
        length--;
    }
    int key[length];
    char ciphertext[length + 1];
    char decrypted[length + 1];
    generate_key(key, length);
    encrypt(plaintext, ciphertext, key, length);
    printf("\nRandom key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\nCiphertext: %s\n", ciphertext);
    decrypt(ciphertext, decrypted, key, length);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}