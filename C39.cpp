#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_SIZE 1000
char most_frequent_english_letters[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void count_letter_frequency(char *ciphertext, int *freq) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
}
void decrypt_with_shift(char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char offset = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = ((ciphertext[i] - offset - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + offset;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  
}
void letter_frequency_attack(char *ciphertext, int top_n) {
    int freq[ALPHABET_SIZE] = {0};
    char possible_plaintext[MAX_CIPHERTEXT_SIZE];
    count_letter_frequency(ciphertext, freq);
    int max_freq = 0, most_frequent_letter_index = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            most_frequent_letter_index = i;
        }
    }
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        int guessed_shift = (most_frequent_letter_index - (most_frequent_english_letters[i] - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt_with_shift(ciphertext, possible_plaintext, guessed_shift);
        printf("Shift %2d (assuming '%c' -> '%c'): %s\n", guessed_shift,
               'A' + most_frequent_letter_index, most_frequent_english_letters[i], possible_plaintext);
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
