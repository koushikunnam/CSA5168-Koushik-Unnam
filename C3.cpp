#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0}; 
    used['J' - 'A'] = 1; 
    int i, j, k = 0;
    for (i = 0; i < strlen(key); i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A']) {
            keyMatrix[k / SIZE][k % SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            keyMatrix[k / SIZE][k % SIZE] = i + 'A';
            k++;
        }
    }
}
void findPosition(char ch, char keyMatrix[SIZE][SIZE], int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void preprocessText(char text[]) {
    int i, len = strlen(text);
    for (i = 0; i < len; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') {
            text[i] = 'I'; 
        }
    }
}
void encrypt(char text[], char keyMatrix[SIZE][SIZE]) {
    int len = strlen(text);
    if (len % 2 != 0) {
        text[len] = 'X';
        text[len + 1] = '\0';
    }
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(text[i], keyMatrix, &row1, &col1);
        findPosition(text[i + 1], keyMatrix, &row2, &col2);
        if (row1 == row2) {
            text[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            text[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        }
        else if (col1 == col2) {
            text[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            text[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        }
        else {
            text[i] = keyMatrix[row1][col2];
            text[i + 1] = keyMatrix[row2][col1];
        }
    }
}
int main() {
    char key[100], text[100];
    char keyMatrix[SIZE][SIZE];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; 
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;  
    createKeyMatrix(key, keyMatrix);
    preprocessText(text);
    encrypt(text, keyMatrix);
    printf("Encrypted message: %s\n", text);
    return 0;
}
