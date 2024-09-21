#include <stdio.h>
#include <ctype.h>
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
char affine_encrypt(char p, int a, int b) {
    if (isalpha(p)) {
        char base = isupper(p) ? 'A' : 'a';
        return (char)((((a * (p - base)) + b) % 26) + base);
    }
    return p; 
}
char affine_decrypt(char c, int a, int b) {
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        int a_inv = mod_inverse(a, 26);
        if (a_inv == -1) {
            printf("Decryption impossible! 'a' has no modular inverse.\n");
            return c;
        }
        return (char)((a_inv * ((c - base - b + 26) % 26)) % 26 + base);
    }
    return c; 
}
int main() {
    char plaintext[256], ciphertext[256], decryptedtext[256];
    int a, b;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of 'b': ");
    scanf("%d", &b);
    if (gcd(a, 26) != 1) {
        printf("'a' must be coprime with 26. Try again.\n");
        return 1;
    }
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affine_encrypt(plaintext[i], a, b);
    }
    printf("Encrypted ciphertext: %s\n", ciphertext);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affine_decrypt(ciphertext[i], a, b);
    }
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}
