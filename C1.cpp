#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char text[], int k) {
    char ch;
    int i;
    for(i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if(isupper(ch)) {
            ch = (ch - 'A' + k) % 26 + 'A';
        }
        else if(islower(ch)) {
            ch = (ch - 'a' + k) % 26 + 'a';
        }
        text[i] = ch; 
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);  
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);
    if(k < 1 || k > 25) {
        printf("Invalid shift value! Please enter a number between 1 and 25.\n");
        return 1;
    }
    encrypt(text, k);
    printf("Encrypted message: %s", text);
    return 0;
}