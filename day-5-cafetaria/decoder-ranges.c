// By Paul G, written in Vienna // 2025-12-05
// I feel like this day calls for some fun with 128 bit integers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef __int128 int128_t; //this is fun
typedef unsigned __int128 uint128_t; //this is also fun

static int128_t range_start[1000];
static int128_t range_end[1000];
int num_ranges = 0;

void swap(int128_t *a, int128_t *b) {
    int128_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_ranges() {
    // Simple bubble sort by start value
    for (int i = 0; i < num_ranges - 1; i++) {
        for (int j = 0; j < num_ranges - i - 1; j++) {
            if (range_start[j] > range_start[j + 1]) {
                swap(&range_start[j], &range_start[j + 1]);
                swap(&range_end[j], &range_end[j + 1]);
            }
        }
    }
}

static char *qtoa(uint128_t n) { //stole that blatantly from https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc
    static char buf[40];
    unsigned int i, j, m = 39;
    memset(buf, 0, 40);
    for (i = 128; i-- > 0;) {
        int carry = !!(n & ((uint128_t)1 << i));
        for (j = 39; j-- > m + 1 || carry;) {
            int d = 2 * buf[j] + carry;
            carry = d > 9;
            buf[j] = carry ? d - 10 : d;
        }
        m = j;
    }
    for (i = 0; i < 38; i++) {
        if (buf[i]) {
            break;
        }
    }
    for (j = i; j < 39; j++) {
        buf[j] += '0';
    }
    return buf + i;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    
    while (fgets(line, 100, f)) { //ranges
        if (line[0] == '\n' || line[0] == '\0') {
            break; // blank line, done with ranges
        }
        long long start, end;
        sscanf(line, "%lld-%lld", &start, &end);
        range_start[num_ranges] = start;
        range_end[num_ranges] = end;
        num_ranges++;
    }
    fclose(f); //forgot that in the recent days
    
    sort_ranges(); //sort ranges from start
    
    int128_t total = 0;
    int128_t cur_start = range_start[0];
    int128_t cur_end = range_end[0];
    
    for (int i = 1; i < num_ranges; i++) {
        if (range_start[i] <= cur_end + 1) {
            if (range_end[i] > cur_end) {//overlapping / adjacent, extend current range
                cur_end = range_end[i];
            }
        } else {
            total += cur_end - cur_start + 1;//gap, count current range and start new one
            cur_start = range_start[i];
            cur_end = range_end[i];
        }
    }
    total += cur_end - cur_start + 1; //count the last range
    printf("final sum pt.2: %s\n", qtoa((uint128_t)total));
    return 0;
}