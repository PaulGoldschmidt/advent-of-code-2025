// By Paul G, written in QR893 @ 33000ft / 2025-12-02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    int position = 50; //start
    int zero_count = 0; //zero transition counter
    char line[256]; //buffer
    while (fgets(line, sizeof(line), file)) {
        char direction = line[0];
        int distance = atoi(line + 1);
        int zeros_this_rotation = 0; //zero transition counter this rotation
        if (direction == 'R') {
            zeros_this_rotation = (position + distance) / 100 - position / 100;
        } else if (direction == 'L') {
            if (position == 0) {
                //starting at 0 first hit is at distance 100
                zeros_this_rotation = distance / 100;
            } else {
                //first hit at step p, then every 100 steps
                if (distance >= position) {
                    zeros_this_rotation = 1 + (distance - position) / 100;
                }
            }
        }

        zero_count += zeros_this_rotation;

        if (direction == 'L') {
            position = ((position - distance) % 100 + 100) % 100;
        } else {
            position = (position + distance) % 100;
        }
    }
    fclose(file);
    printf("password pt. 2: %d\n", zero_count);
    return 0;
}