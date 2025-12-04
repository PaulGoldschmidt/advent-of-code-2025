// By Paul G, written at Home / 2025-12-04

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char grid[140][140];
int rows = 0;
int cols = 0;

int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1}; //accessing dirs
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int count(int r, int c) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        // Check bounds
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (grid[nr][nc] == '@') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    FILE *f = fopen("input.txt", "r");

    while (fgets(grid[rows], 140, f)) {
        int len = strlen(grid[rows]);
        cols = len;
        rows++; //count
    }

    int total = 0; //var result

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '@') {
                int adjacent = count(r, c);
                if (adjacent < 4) {
                    total++;
                    printf("accessible roll at (%d, %d) with %d adjacent rolls\n", r, c, adjacent); //debug
                }
            }
        }
    }
    
    fclose(f);

    printf("\nfinal sum: %d\n", total);

    return 0;
}