// By Paul G, rewritten in ICE 572 // 2025-12-27
// Also taken inspo for the lower/upper-boundings from here: https://github.com/TurtleSmoke/Advent-of-Code/blob/main/2025/day_12/main.py
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHAPES 10

static int shape_cells[MAX_SHAPES];    // count of # in shape
static int shape_bbox[MAX_SHAPES];     // bounding box area (width * height)
int nshapes = 0;

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[256];
    
    while (fgets(line, 256, f)) { // parse shapes
        if (line[0] == '\n' || line[0] == '\0') continue;
        if (line[0] >= '0' && line[0] <= '9' && strchr(line, ':') && !strchr(line, 'x')) {
            int idx;
            sscanf(line, "%d:", &idx);
            int cells = 0, width = 0, height = 0;
            for (int row = 0; row < 10; row++) {
                if (!fgets(line, 256, f) || line[0] == '\n' || line[0] == '\0') break;
                int len = 0;
                for (int col = 0; line[col] && line[col] != '\n'; col++) {
                    if (line[col] == '#') cells++;
                    len = col + 1;
                }
                if (len > width) width = len;
                height++;
            }
            shape_cells[idx] = cells;
            shape_bbox[idx] = width * height;
            if (idx >= nshapes) nshapes = idx + 1;
        } else if (strchr(line, 'x')) {
            break;
        }
    }
    
    int lower = 0, upper = 0;
    do { // parse regions
        if (!strchr(line, 'x')) continue;
        int W, H;
        sscanf(line, "%dx%d:", &W, &H);
        char *p = strchr(line, ':') + 1;
        int need[MAX_SHAPES] = {0};
        int idx = 0;
        while (*p && idx < nshapes) {
            while (*p == ' ') p++;
            if (*p >= '0' && *p <= '9') { need[idx++] = atoi(p); while (*p >= '0' && *p <= '9') p++; }
            else break;
        }
        
        int area = W * H;
        int sum_cells = 0, sum_bbox = 0;
        for (int i = 0; i < nshapes; i++) {
            sum_cells += need[i] * shape_cells[i];
            sum_bbox += need[i] * shape_bbox[i];
        }
        
        if (sum_cells <= area) lower++;
        if (sum_bbox <= area) upper++;
    } while (fgets(line, 256, f));
    
    fclose(f);
    
    printf("lower: %d, upper: %d\n", lower, upper); // should match otherwise bruteforcing needs to be implemented
    printf("\nfinal sum: %d\n", lower);
    return 0;
}