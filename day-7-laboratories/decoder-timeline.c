// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <string.h>

static char grid[200][200];
static long long timelines[200][200]; // count of timelines, finally using long long again haha
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
    
    // initialize single particle at S
    timelines[0][start_col] = 1;
    
    // simulate row by row
    for (int r = 0; r < rows - 1; r++) {
        for (int c = 0; c < cols; c++) {
            if (timelines[r][c] > 0) {
                // particle moves down
                int next_r = r + 1;
                if (grid[next_r][c] == '^') {
                    // hit splitter - timeline splits left and right
                    if (c > 0) timelines[next_r][c-1] += timelines[r][c];
                    if (c < cols-1) timelines[next_r][c+1] += timelines[r][c];
                } else {
                    // continue down
                    timelines[next_r][c] += timelines[r][c];
                }
            }
        }
    }
    
    // count total timelines at the bottom row
    long long total = 0;
    for (int c = 0; c < cols; c++) {
        total += timelines[rows-1][c];
    }
    
    printf("final sum pt.2: %lld\n", total);
    return 0;
}