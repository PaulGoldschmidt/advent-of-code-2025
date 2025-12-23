// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <stdlib.h>

static long long tile_x[10000];
static long long tile_y[10000];
int num_tiles = 0;

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    
    while (fgets(line, 100, f)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        long long x, y;
        sscanf(line, "%lld,%lld", &x, &y);
        tile_x[num_tiles] = x;
        tile_y[num_tiles] = y;
        num_tiles++;
    }
    fclose(f);
    
    long long total = 0; //var result (max area)
    
    for (int i = 0; i < num_tiles; i++) {
        for (int j = i + 1; j < num_tiles; j++) {
            long long dx = tile_x[i] - tile_x[j];
            if (dx < 0) dx = -dx;
            long long dy = tile_y[i] - tile_y[j];
            if (dy < 0) dy = -dy;
            long long area = (dx + 1) * (dy + 1);
            if (area > total) {
                total = area;
                printf("tiles (%lld,%lld) and (%lld,%lld) -> area %lld\n", 
                       tile_x[i], tile_y[i], tile_x[j], tile_y[j], area); //debug because I'm stupid
            }
        }
    }
    
    printf("\nfinal sum: %lld\n", total);
    return 0;
}