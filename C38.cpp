#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
int determinant(int matrix[SIZE][SIZE], int n) {
    int det = 0;
    int submatrix[SIZE][SIZE];
    
    if (n == 2) {
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    } else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x) {
                        continue;
                    }
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
        }
    }
    return det;
}
int modInverse(int a, int mod) {
    a = a % mod;
    for (int x = 1; x < mod; x++) {
        if ((a * x) % mod == 1) {
            return x;
        }
    }
    return -1; 
}
void cofactor(int matrix[SIZE][SIZE], int temp[SIZE][SIZE], int p, int q, int n) {
    int i = 0, j = 0;
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
void adjoint(int matrix[SIZE][SIZE], int adj[SIZE][SIZE]) {
    int sign = 1, temp[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cofactor(matrix, temp, i, j, SIZE);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign * determinant(temp, SIZE - 1)) % 26;
        }
    }
}
int inverseMatrix(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = determinant(matrix, SIZE);
    det = det % 26;
    if (det == 0) {
        printf("Matrix is not invertible\n");
        return 0;
    }
    
    int det_inv = modInverse(det, 26);
    if (det_inv == -1) {
        printf("No modular inverse exists for determinant\n");
        return 0;
    }

    int adj[SIZE][SIZE];
    adjoint(matrix, adj);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inverse[i][j] = (adj[i][j] * det_inv) % 26;
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }
    return 1;
}
void encrypt(int key[SIZE][SIZE], int plaintext[SIZE], int ciphertext[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        ciphertext[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i] += key[i][j] * plaintext[j];
        }
        ciphertext[i] %= 26;
    }
}
void known_plaintext_attack(int plaintext_matrix[SIZE][SIZE], int ciphertext_matrix[SIZE][SIZE], int key[SIZE][SIZE]) {
    int inverse_plaintext[SIZE][SIZE];
    
    if (!inverseMatrix(plaintext_matrix, inverse_plaintext)) {
        printf("Plaintext matrix is not invertible\n");
        return;
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            key[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                key[i][j] += ciphertext_matrix[i][k] * inverse_plaintext[k][j];
            }
            key[i][j] %= 26;
        }
    }
}

int main() {
    int key[SIZE][SIZE] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; 
    int plaintext[SIZE] = {7, 4, 11}; 
    int ciphertext[SIZE];
    encrypt(key, plaintext, ciphertext);
    
    printf("Encrypted ciphertext: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%c", ciphertext[i] + 'A');
    }
    printf("\n");
    int plaintext_matrix[SIZE][SIZE] = {{7, 4, 11}, {0, 19, 14}, {3, 0, 4}};  
    int ciphertext_matrix[SIZE][SIZE] = {{10, 14, 9}, {2, 3, 24}, {9, 23, 5}}; 

    int recovered_key[SIZE][SIZE];
    known_plaintext_attack(plaintext_matrix, ciphertext_matrix, recovered_key);
    
    printf("Recovered key matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", recovered_key[i][j]);
        }
        printf("\n");
    }

    return 0;
}
