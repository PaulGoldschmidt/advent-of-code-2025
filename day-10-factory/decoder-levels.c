// By Paul G, rewritten in ICE 572 // 2025-12-23 and 2025-12-27
// Use rational Gaussian elimination; havely inspired by what Z3 does internally
// to solve LPPs with given integer constraints

// Shoutout to Lukas Kollmer helping me found a solution https://github.com/lukaskollmer/advent-of-code/blob/main/src/2025/day_10/solution.ml
// This was so far by far the hardest problem. This SHOULD NOT BE a benchmark for my perfomance as a swe as I used a lot of external help here, including:
// https://www.codewithc.com/c-program-for-gauss-elimination-method/
// https://math.mit.edu/~dav/gauss19.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int buttons[20][12];
int num_buttons;
int num_counters;
int target[12];
int best;

double mat[12][21];
int pivot_col[12]; // pivot column -> row
int n_pivots;

void solve_lp() {
    // Build augmented matrix
    // mat[i][j] = buttons[j][i], mat[i][num_buttons] = target[i]
    for (int i = 0; i < num_counters; i++) {
        for (int j = 0; j < num_buttons; j++)
            mat[i][j] = buttons[j][i];
        mat[i][num_buttons] = target[i];
    }
    
    // Gaussian elimination algo magiccccccc
    n_pivots = 0;
    for (int col = 0; col < num_buttons && n_pivots < num_counters; col++) {
        // Find pivot
        int piv = -1;
        for (int r = n_pivots; r < num_counters; r++) {
            if (mat[r][col] != 0) { piv = r; break; }
        }
        if (piv < 0) continue;
        
        // Swap rows
        for (int c = 0; c <= num_buttons; c++) {
            double t = mat[n_pivots][c];
            mat[n_pivots][c] = mat[piv][c];
            mat[piv][c] = t;
        }
        
        // Scale pivot row
        double scale = mat[n_pivots][col];
        for (int c = 0; c <= num_buttons; c++)
            mat[n_pivots][c] /= scale;
        
        // Eliminate
        for (int r = 0; r < num_counters; r++) {
            if (r != n_pivots && mat[r][col] != 0) {
                double f = mat[r][col];
                for (int c = 0; c <= num_buttons; c++)
                    mat[r][c] -= f * mat[n_pivots][c];
            }
        }
        pivot_col[n_pivots] = col;
        n_pivots++;
    }
    
    // Free variables
    int free_vars[20], n_free = 0;
    int is_pivot[20] = {0};
    for (int i = 0; i < n_pivots; i++) is_pivot[pivot_col[i]] = 1;
    for (int j = 0; j < num_buttons; j++)
        if (!is_pivot[j]) free_vars[n_free++] = j;
    
    // Try all combinations of free variables, bounded by targets
    int max_free[20];
    for (int f = 0; f < n_free; f++) {
        int col = free_vars[f];
        max_free[f] = 0;
        for (int i = 0; i < num_counters; i++)
            if (target[i] > max_free[f]) max_free[f] = target[i];
    }
    
    // Enumerate free variable assignments
    long long iters = 1;
    for (int f = 0; f < n_free; f++) iters *= (max_free[f] + 1);
    if (iters > 100000000LL) {
        // free vars = 0
        int x[20] = {0};
        int valid = 1, sum = 0;
        for (int r = n_pivots - 1; r >= 0 && valid; r--) {
            double val = mat[r][num_buttons];
            for (int c = pivot_col[r] + 1; c < num_buttons; c++)
                val -= mat[r][c] * x[c];
            int iv = (int)(val + 0.5);
            if (iv < 0 || (val - iv > 1e-6 || iv - val > 1e-6)) valid = 0;
            else { x[pivot_col[r]] = iv; sum += iv; }
        }
        if (valid) best = sum;
        return;
    }
    
    int fv[20] = {0};
    while (1) {
        // Compute pivot variables from free variables
        int x[20];
        for (int f = 0; f < n_free; f++) x[free_vars[f]] = fv[f];
        
        int valid = 1, sum = 0;
        for (int f = 0; f < n_free; f++) sum += fv[f];
        
        for (int r = n_pivots - 1; r >= 0 && valid; r--) {
            double val = mat[r][num_buttons];
            for (int c = pivot_col[r] + 1; c < num_buttons; c++)
                val -= mat[r][c] * x[c];
            int iv = (int)(val + 0.5);
            if (iv < 0 || (val - iv > 1e-6 || iv - val > 1e-6)) valid = 0;
            else { x[pivot_col[r]] = iv; sum += iv; }
        }
        
        if (valid && sum < best) best = sum;
        
        // mv forward
        int carry = 1;
        for (int f = 0; f < n_free && carry; f++) {
            fv[f]++;
            if (fv[f] > max_free[f]) fv[f] = 0;
            else carry = 0;
        }
        if (carry) break;
    }
}

int main() {
    clock_t start = clock();
    FILE *f = fopen("input.txt", "r");
    char line[1000];
    int total = 0;
    int machine_num = 0;
    
    while (fgets(line, 1000, f)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        machine_num++;
        
        char *p = strchr(line, '{');
        p++;
        num_counters = 0;
        while (*p != '}') {
            if (*p >= '0' && *p <= '9') {
                int num = 0;
                while (*p >= '0' && *p <= '9') {
                    num = num * 10 + (*p - '0');
                    p++;
                }
                target[num_counters++] = num;
            } else p++;
        }
        
        num_buttons = 0;
        memset(buttons, 0, sizeof(buttons));
        p = line;
        while ((p = strchr(p, '(')) != NULL) {
            p++;
            while (*p != ')') {
                if (*p >= '0' && *p <= '9') {
                    int num = 0;
                    while (*p >= '0' && *p <= '9') {
                        num = num * 10 + (*p - '0');
                        p++;
                    }
                    buttons[num_buttons][num] = 1;
                } else p++;
            }
            num_buttons++;
            char *next_paren = strchr(p, '(');
            char *curly = strchr(p, '{');
            if (curly && (!next_paren || curly < next_paren)) break;
        }
        
        best = INT_MAX;
        solve_lp();
        printf("machine %d needs %d presses\n", machine_num, best);
        total += best;
    }
    fclose(f);
    printf("\nfinal sum pt.2: %d\n", total);
    printf("exec time: %.3f ms\n", (clock() - start) * 1000.0 / CLOCKS_PER_SEC);
    return 0;
}
