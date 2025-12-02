// By Paul G, written at Berlin Hauptbahnhof, 2025-12-02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isInvalidID(unsigned long long num) {
    char str[32];
    sprintf(str, "%llu", num);
    
    int len = strlen(str);

    for (int patLen = 1; patLen <= len / 2; patLen++) {
        if (len % patLen != 0) { //must divide evenly into total length
            continue;
        }

        bool valid = true;
        
        for (int i = patLen; i < len && valid; i++) { //pattern repeats throughout the string
            if (str[i] != str[i % patLen]) {
                valid = false;
            }
        }

        if (valid) {
            return true;
        }
    }

    return false;
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

    printf("\nfinal sum: %llu\n", totalSum);
    free(inputCopy);
    free(input);

    return 0;
}