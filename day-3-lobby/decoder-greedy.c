// By Paul G, written at HAW Hamburg 110 / 2025-12-03
// Adoped from https://www.geeksforgeeks.org/dsa/introduction-to-greedy-algorithm-data-structures-and-algorithm-tutorials/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_DIGITS = 12;

long long calc_joltage(const char *bank, int len) {
    char result[NUM_DIGITS + 1];
    int start = 0;
    for (int i = 0; i < NUM_DIGITS; i++) {
        int end = len - (NUM_DIGITS - i - 1);
        int best_pos = start;
        char best_digit = bank[start];
        for (int j = start; j < end; j++) {
            if (bank[j] > best_digit) {
                best_digit = bank[j];
                best_pos = j;
            }
        }
        result[i] = best_digit;
        start = best_pos + 1;
    }
    result[NUM_DIGITS] = '\0';

    long long value = 0; //converter
    for (int i = 0; i < NUM_DIGITS; i++) {
        value = value * 10 + (result[i] - '0');
    }

    return value;
    }


int main(void) {
    char line[10000];
    long long total = 0;
    FILE *f = fopen("input.txt", "r");

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);
        while (len > 0 && isspace(line[len - 1])) {
            line[--len] = '\0';
        }
        long long joltage = calc_joltage(line, len);
        total += joltage;
    }
    
    printf("\nfinal sum pt. 2: %llu\n", total);
    fclose(f);
    return 0;
}
