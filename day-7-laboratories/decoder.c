// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <string.h>

static char grid[200][200];
static int beams[200][200];
int rows = 0;
int cols = 0;

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[200];
    
    while (fgets(line, 200, f)) {
        int len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0';
        len = strlen(line);
        if (len > cols) cols = len;
        strcpy(grid[rows], line);
        rows++;
    }
    fclose(f);
    
    // find S
    int start_col = 0;
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == 'S') {
            start_col = c;
            break;
        }
    }
    
    // initialize beam at S
    beams[0][start_col] = 1;
    
    int total_splits = 0;
    
    // simulate row by row
    // i think this could be a cool simulation graphic, maybe for later
    for (int r = 0; r < rows - 1; r++) {
        for (int c = 0; c < cols; c++) {
            if (beams[r][c] == 1) {
                // beam moves down
                int next_r = r + 1;
                if (grid[next_r][c] == '^') {
                    total_splits++;
                    if (c > 0) beams[next_r][c-1] = 1;
                    if (c < cols-1) beams[next_r][c+1] = 1;
                } else {
                    // continue down
                    beams[next_r][c] = 1;
                }
            }
        }
    }
    
    printf("total splits: %d\n", total_splits);
    return 0;
}
