#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_SIZE 1000
char english_letter_frequency[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void count_letter_frequency(char *ciphertext, int *freq) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
}
void map_cipher_to_plain(char *ciphertext, char *plaintext, char *mapping) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char is_lower = islower(ciphertext[i]);
            char mapped_letter = mapping[toupper(ciphertext[i]) - 'A'];
            plaintext[i] = is_lower ? tolower(mapped_letter) : mapped_letter;
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
void letter_frequency_attack(char *ciphertext, int top_n) {
    int freq[ALPHABET_SIZE] = {0};
    int sorted_freq[ALPHABET_SIZE];
    char possible_plaintext[MAX_CIPHERTEXT_SIZE];
    char ciphertext_to_plaintext[ALPHABET_SIZE];
    count_letter_frequency(ciphertext, freq);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_freq[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[sorted_freq[i]] < freq[sorted_freq[j]]) {
                int temp = sorted_freq[i];
                sorted_freq[i] = sorted_freq[j];
                sorted_freq[j] = temp;
            }
        }
    }

    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int guess = 0; guess < top_n; guess++) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            ciphertext_to_plaintext[sorted_freq[i]] = english_letter_frequency[(i + guess) % ALPHABET_SIZE];
        }
        map_cipher_to_plain(ciphertext, possible_plaintext, ciphertext_to_plaintext);
        printf("Guess %2d: %s\n", guess + 1, possible_plaintext);
    }
}
int main() {
    char ciphertext[MAX_CIPHERTEXT_SIZE];
    int top_n;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_CIPHERTEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);
    letter_frequency_attack(ciphertext, top_n);

    return 0;
}
