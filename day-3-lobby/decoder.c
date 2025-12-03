// By Paul G, written at HAW Hamburg 422A / 2025-12-03

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int calc_joltage(const char *bank, int len) {
    int max = 0;
    for (int i = 0; i < len - 1; i++) { // Try all pairs (a, b) where a < b
        for (int j = i + 1; j < len; j++) {
            int val = (bank[i] - '0') * 10 + (bank[j] - '0');
            if (val > max) {
                max = val;
            }
        }
    }
    
    return max;
}

int main(void) {
    char line[10000];
    long long total = 0;
    FILE *f = fopen("input.txt", "r");

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);
        int joltage = calc_joltage(line, len);
        total += joltage;
    }
    
    printf("%lld\n", total);
    fclose(f);
    return 0;
}
