#include <stdio.h>
#include <string.h>
#include <ctype.h>
char encryptChar(char plaintext, char key) {
    plaintext = toupper(plaintext);
    key = toupper(key);
    return ((plaintext - 'A' + (key - 'A')) % 26) + 'A';
}
void encryptMessage(char plaintext[], char key[], char ciphertext[]) {
    int i, j = 0;
    int keyLen = strlen(key);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            ciphertext[i] = encryptChar(plaintext[i], key[j % keyLen]);
            j++;  
        } else {
            ciphertext[i] = plaintext[i];  
        }
    }
    ciphertext[i] = '\0';  
}
int main() {
    char plaintext[100], key[100], ciphertext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    encryptMessage(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
