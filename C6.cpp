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
void solveAffineCipher(int C1, int P1, int C2, int P2, int *a, int *b) {
    int diffC = (C1 - C2 + 26) % 26;
    int diffP = (P1 - P2 + 26) % 26;
    *a = (diffC * modInverse(diffP, 26)) % 26;
    *b = (C1 - (*a * P1) % 26 + 26) % 26;
}
int main() {
    char ciphertext[] = "BUDXYZ"; 
    int a, b;
    int C1 = 1, P1 = 4; 
    int C2 = 20, P2 = 19; 
    solveAffineCipher(C1, P1, C2, P2, &a, &b);
    printf("Derived keys: a = %d, b = %d\n", a, b);
    char decrypted[100];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decrypted[i] = affineDecryptChar(ciphertext[i], a, b);
    }
    decrypted[sizeof(ciphertext) - 1] = '\0';
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}

