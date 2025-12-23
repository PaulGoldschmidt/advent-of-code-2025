// By Paul G, rewritten in ICE 572 // 2025-12-23
// this can be ignored: "ld: warning: reducing alignment of section __DATA,__common from 0x8000 to 0x4000 because it exceeds segment maximum alignment"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char grid[10][4000]; // exact dimensions of input.txt: 5 row x 3739 cols
int rows = 0;
int cols = 0;

int main() {
    FILE *f = fopen("input.txt", "r");
    
    while (fgets(grid[rows], 4000, f)) {
        int len = strlen(grid[rows]);
        if (len > cols) cols = len;
        rows++;
    }
    fclose(f);
    
    long long grand_total = 0;
    int c = cols - 1;
    
    while (c >= 0) {
        // skip separators
        int all_space = 1;
        for (int r = 0; r < rows; r++) {
            if (c < strlen(grid[r]) && grid[r][c] != ' ' && grid[r][c] != '\n') {
                all_space = 0;
                break;
            }
        }
        if (all_space) {
            c--;
            continue;
        }
        
        // find end, going l.eft
        int end = c;
        int start = c;
        while (start >= 0) {
            int blank_col = 1;
            for (int r = 0; r < rows; r++) {
                if (start < strlen(grid[r]) && grid[r][start] != ' ' && grid[r][start] != '\n') {
                    blank_col = 0;
                    break;
                }
            }
            if (blank_col) break;
            start--;
        }
        start++; // move back to first non-blank column
        
        // extract operator last row
        char op = '+';
        for (int i = start; i <= end; i++) {
            if (grid[rows-1][i] == '*' || grid[rows-1][i] == '+') {
                op = grid[rows-1][i];
                break;
            }
        }
        
        // process columns right-to-left nowwwww
        long long result = (op == '*') ? 1 : 0;
        for (int col = end; col >= start; col--) {
            // build number from top to bottom, most to least sig
            char num_str[20] = {0};
            int k = 0;
            for (int r = 0; r < rows - 1; r++) {
                if (col < strlen(grid[r]) && isdigit(grid[r][col])) {
                    num_str[k++] = grid[r][col];
                }
            }
            if (k > 0) {
                long long num = atoll(num_str);
                if (op == '*') {
                    result *= num;
                } else {
                    result += num;
                }
            }
        }
        
        grand_total += result;
        c = start - 1;
    }
    
    printf("final sum: %lld\n", grand_total);
    return 0;
}