// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <stdlib.h>

static int tile_x[1000];
static int tile_y[1000];
int num_tiles = 0;

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    
    while (fgets(line, 100, f)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        int x, y;
        sscanf(line, "%d,%d", &x, &y);
        tile_x[num_tiles] = x;
        tile_y[num_tiles] = y;
        num_tiles++;
    }
    fclose(f);
    
    int total = 0; //var result (max area)
    
    for (int i = 0; i < num_tiles; i++) {
        for (int j = i + 1; j < num_tiles; j++) {
            int dx = tile_x[i] - tile_x[j];
            if (dx < 0) dx = -dx;
            int dy = tile_y[i] - tile_y[j];
            if (dy < 0) dy = -dy;
            int area = (dx + 1) * (dy + 1);
            if (area > total) {
                total = area;
                printf("tiles (%d,%d) and (%d,%d) -> area %d\n", 
                       tile_x[i], tile_y[i], tile_x[j], tile_y[j], area);
            }
        }
    }
    
    printf("\nfinal sum: %d\n", total);
    return 0;
}
