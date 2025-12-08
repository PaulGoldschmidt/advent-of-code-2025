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
    int removed = 0;
    
    do {
        removed = 0;
        for (int r = 0; r < rows; r++) { //mark rolls to remove
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '@') {
                    int adjacent = count(r, c);
                    if (adjacent < 4) {
                        grid[r][c] = 'x'; //mark for remval
                        removed++;
                    }
                }
            }
        }
        for (int r = 0; r < rows; r++) { //remove marked rolls
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 'x') {
                    grid[r][c] = '.'; // remove
                }
            }
        }
        total += removed;
        printf("Removed %d rolls this iteration\n", removed); //debug
    } while (removed > 0);
    
    fclose(f);

    printf("\nfinal sum pt.2 : %d\n", total);

    return 0;
}