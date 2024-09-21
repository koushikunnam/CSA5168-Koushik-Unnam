#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char english_freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void count_frequency(const char *ciphertext, int *freq) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
        }
    }
}
void sort_by_frequency(int *freq, char *letters) {
    for (int i = 0; i < 26; i++) {
        letters[i] = 'A' + i;
    }
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[i] < freq[j]) {
                int temp_freq = freq[i];
                freq[i] = freq[j];
                freq[j] = temp_freq;

                char temp_letter = letters[i];
                letters[i] = letters[j];
                letters[j] = temp_letter;
            }
        }
    }
}
void substitute_letters(const char *ciphertext, const char *cipher_freq, const char *target_freq, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);
        if (c >= 'A' && c <= 'Z') {
            char *pos = strchr(cipher_freq, c);
            if (pos != NULL) {
                int index = pos - cipher_freq;
                plaintext[i] = target_freq[index];
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
int main() {
    char ciphertext[1024];
    int freq[26] = {0};
    char cipher_freq[26];
    char plaintext[1024];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    if (ciphertext[strlen(ciphertext) - 1] == '\n') {
        ciphertext[strlen(ciphertext) - 1] = '\0'; 
    }
    count_frequency(ciphertext, freq);
    sort_by_frequency(freq, cipher_freq);
    printf("\nTop 10 possible plaintexts:\n");
    for (int i = 0; i < 10; i++) {
        substitute_letters(ciphertext, cipher_freq, english_freq + i, plaintext);
        printf("Plaintext %d: %s\n", i + 1, plaintext);
    }
    return 0;
}