// By Paul G, written in QR893 @ 33000ft / 2025-12-02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    int position = 50; //start
    int zero_count = 0; //how often zero was hit
    char line[256]; //buffer
    while (fgets(line, sizeof(line), file)) {
        char direction = line[0];
        int distance = atoi(line + 1);
        if (direction == 'L') {
            position = (position - distance) % 100;
            // c hacks
            if (position < 0) position += 100;
        } else if (direction == 'R') {
            // add distance
            position = (position + distance) % 100;
        }
        if (position == 0) {
            zero_count++;
        }
        }
    
    fclose(file);
    printf("password: %d\n", zero_count);
    return 0;
}