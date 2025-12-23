// By Paul G, rewritten in ICE 572 // 2025-12-23
// Galoisfield button pressing decoding programm, brute-forcing all combinations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[1000];
    int total = 0;
    
    while (fgets(line, 1000, f)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        
        // parse target pattern from [...]
        char *p = strchr(line, '[');
        p++;
        int num_lights = 0;
        int target = 0;
        while (*p != ']') {
            if (*p == '#') target |= (1 << num_lights);
            num_lights++;
            p++;
        }
        
        // parse buttons from (...)
        int buttons[20];
        int num_buttons = 0;
        p = line;
        while ((p = strchr(p, '(')) != NULL) {
            p++;
            if (*p == ')') {
                // empty button
                continue;
            }
            int mask = 0;
            while (*p != ')') {
                if (*p >= '0' && *p <= '9') {
                    int num = 0;
                    while (*p >= '0' && *p <= '9') {
                        num = num * 10 + (*p - '0');
                        p++;
                    }
                    mask |= (1 << num);
                } else {
                    p++;
                }
            }
            buttons[num_buttons++] = mask;
            // early stop before hitting {
            if (strchr(p, '{') && strchr(p, '{') < strchr(p, '(')) break;
            char *next_paren = strchr(p, '(');
            char *curly = strchr(p, '{');
            if (curly && (!next_paren || curly < next_paren)) break;
        }
        
        // brute force all!
        int min_presses = 999999;
        for (int combo = 0; combo < (1 << num_buttons); combo++) {
            int state = 0;
            int presses = 0;
            for (int b = 0; b < num_buttons; b++) {
                if (combo & (1 << b)) {
                    state ^= buttons[b];
                    presses++;
                }
            }
            if (state == target && presses < min_presses) {
                min_presses = presses;
            }
        }
        
        printf("this machine needs %d presses\n", min_presses);
        total += min_presses;
    }
    
    fclose(f);
    printf("\nfinal sum: %d\n", total);
    return 0;
}