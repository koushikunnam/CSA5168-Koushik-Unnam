#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void encrypt(char text[], char substitution[]) {
    char ch;
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = substitution[ch - 'A'];
        }
        else if (islower(ch)) {
            text[i] = tolower(substitution[ch - 'a']);
        }
    }
}
int main() {
    char text[100];
    char substitution[ALPHABET_SIZE + 1];  
    strcpy(substitution, "QWERTYUIOPLKJHGFDSAZXCVBNM");
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);  
    encrypt(text, substitution);
    printf("Encrypted message: %s", text);
    return 0;
}
