// By Paul G, written at HAW Hamburg 110 / 2025-12-03
// Adoped from https://www.geeksforgeeks.org/dsa/introduction-to-greedy-algorithm-data-structures-and-algorithm-tutorials/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char line[10000];
    long long total = 0;
    FILE *f = fopen("input.txt", "r");

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);
        int joltage = calc_joltage(line, len);
        total += joltage;
    }
    
    printf("\nfinal sum: %llu\n", total);
    fclose(f);
    return 0;
}
