// By Paul G, written in Vienna // 2025-12-05
// This uses one to many long long types
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long range_start[1000];
static long long range_end[1000];
int num_ranges = 0;

static long long ingredients[1000];
int num_ingredients = 0;

int is_fresh(long long id) { //quick check
    for (int i = 0; i < num_ranges; i++) {
        if (id >= range_start[i] && id <= range_end[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    
    while (fgets(line, 100, f)) { // ranges
        if (line[0] == '\n' || line[0] == '\0') {
            break; // blank line, switch to ingredients
        }
        long long start, end;
        sscanf(line, "%lld-%lld", &start, &end);
        range_start[num_ranges] = start;
        range_end[num_ranges] = end;
        num_ranges++;
    }
    
    while (fgets(line, 100, f)) { // ingredient IDs
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        long long id; 
        sscanf(line, "%lld", &id);
        ingredients[num_ingredients] = id;
        num_ingredients++;
    }
    fclose(f);
    
    int total = 0; //var result
    for (int i = 0; i < num_ingredients; i++) {
        long long id = ingredients[i];
        if (is_fresh(id)) {
            total++;
            printf("ingredient %lld is fresh\n", id); //debug
        }
    }
    
    printf("\nfinal sum: %d\n", total);
    return 0;
}