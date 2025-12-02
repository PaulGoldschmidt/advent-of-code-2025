// By Paul G, written at DOH Airport / 2025-12-02
// Base Idea here to check if a number's string representation is of the form >XX< where >X< is some string
// Was planing to use a Knuth-Morris-Pratt Algorithm (https://www.geeksforgeeks.org/c/kmp-algorithm-for-pattern-searching-in-c/) to do pattern searching but this seems like the simpler approach

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isInvalidID(unsigned long long num) {
    char str[32];
    sprintf(str, "%llu", num);
    
    int len = strlen(str);
    if (len % 2 != 0) {
        return false;
    }
    
    int half = len / 2;
    
    for (int i = 0; i < half; i++) { // first half equals second half?
        if (str[i] != str[half + i]) {
            return false;
        }
    }
    
    return true;
}

unsigned long long processRange(const char* range) { //compute full range to account for all invalid IDs, add to sum
    unsigned long long start, end;
    sscanf(range, "%llu-%llu", &start, &end);
    
    unsigned long long sum = 0;
    
    for (unsigned long long id = start; id <= end; id++) {
        if (isInvalidID(id)) {
            printf("invalid ID: %llu\n", id);
            sum += id;
        }
    }
    
    return sum;
}

int main() {    
    char* input = NULL;    
    // Read from file
    FILE* f = fopen("input.txt", "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    input = malloc(fsize + 1);
    fread(input, 1, fsize, f);
    input[fsize] = '\0';
    fclose(f);

    char* inputCopy = strdup(input); //strtok modifies the string
    unsigned long long totalSum = 0;

    char* token = strtok(inputCopy, ",");
    while (token != NULL) {
        if (strlen(token) > 0) {
            totalSum += processRange(token);
        }
        token = strtok(NULL, ",");
    }

    printf("\final sum: %llu\n", totalSum);
    free(inputCopy);
    free(input);

    return 0;
}