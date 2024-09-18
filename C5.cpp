#include <stdio.h>
#include <ctype.h>
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
char affineEncryptChar(char p, int a, int b) {
    if (isalpha(p)) {
        p = toupper(p) - 'A'; 
        return ((a * p + b) % 26) + 'A'; 
    }
    return p; 
}
char affineDecryptChar(char c, int a, int b) {
    if (isalpha(c)) {
        c = toupper(c) - 'A'; 
        int a_inv = modInverse(a, 26);
        if (a_inv == -1) {
            printf("Multiplicative inverse does not exist, decryption impossible.\n");
            return c;
        }
        return ((a_inv * (c - b + 26)) % 26) + 'A'; 
    }
    return c; 
}
int main() {
    int a = 5, b = 8; 
    char plaintext[] = "HELLOAFFINE";
    char encrypted[100], decrypted[100];
    for (int i = 0; plaintext[i] != '\0'; i++) {
        encrypted[i] = affineEncryptChar(plaintext[i], a, b);
    }
    encrypted[sizeof(plaintext) - 1] = '\0';
    for (int i = 0; encrypted[i] != '\0'; i++) {
        decrypted[i] = affineDecryptChar(encrypted[i], a, b);
    }
    decrypted[sizeof(plaintext) - 1] = '\0';
    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    return 0;
}
