// By Paul G, rewritten in ICE 572 // 2025-12-23
// this was a process haha, so far hardest challenge
// the programm crashes with "EXC_BAD_ACCESS (code=1, address=XYZ)", but only after not freeing up memory when done with calculation

#include <stdio.h>
#include <stdlib.h>

static long long tile_x[10000];
static long long tile_y[10000];
int num_tiles = 0;

// check if point is inside or on the polygon using ray casting
int point_in_polygon(long long px, long long py) {
    int inside = 0;
    for (int i = 0; i < num_tiles; i++) {
        int j = (i + 1) % num_tiles;
        long long x1 = tile_x[i], y1 = tile_y[i];
        long long x2 = tile_x[j], y2 = tile_y[j];
        
        // check if point is on this edge
        if (x1 == x2 && px == x1) { // vertical
            long long miny = (y1 < y2) ? y1 : y2;
            long long maxy = (y1 > y2) ? y1 : y2;
            if (py >= miny && py <= maxy) return 1;
        }
        if (y1 == y2 && py == y1) { // horizontal
            long long minx = (x1 < x2) ? x1 : x2;
            long long maxx = (x1 > x2) ? x1 : x2;
            if (px >= minx && px <= maxx) return 1;
        }
    }
    // ray casting
    for (int i = 0; i < num_tiles; i++) {
        int j = (i + 1) % num_tiles;
        long long x1 = tile_x[i], y1 = tile_y[i];
        long long x2 = tile_x[j], y2 = tile_y[j];
        if (y1 == y2) continue; // horizontal skip
        if (py < (y1 < y2 ? y1 : y2)) continue;
        if (py >= (y1 > y2 ? y1 : y2)) continue;
        long long xint = x1 + (py - y1) * (x2 - x1) / (y2 - y1);
        if (px < xint) inside = !inside;
    }
    return inside;
}

// check if rectangle is fully inside polygon
int rect_valid(long long minx, long long miny, long long maxx, long long maxy) {
    if (!point_in_polygon(minx, miny)) return 0;
    if (!point_in_polygon(minx, maxy)) return 0;
    if (!point_in_polygon(maxx, miny)) return 0;
    if (!point_in_polygon(maxx, maxy)) return 0;
    
    // check if any polygon edge crosses through the rectange interior
    for (int i = 0; i < num_tiles; i++) {
        int j = (i + 1) % num_tiles;
        long long x1 = tile_x[i], y1 = tile_y[i];
        long long x2 = tile_x[j], y2 = tile_y[j];
        
        if (x1 == x2) { // vertical
            if (x1 > minx && x1 < maxx) {
                long long ey1 = (y1 < y2) ? y1 : y2;
                long long ey2 = (y1 > y2) ? y1 : y2;
                if (ey1 < maxy && ey2 > miny) return 0;
            }
        } else { // horizontal
            if (y1 > miny && y1 < maxy) {
                long long ex1 = (x1 < x2) ? x1 : x2;
                long long ex2 = (x1 > x2) ? x1 : x2;
                if (ex1 < maxx && ex2 > minx) return 0;
            }
        }
    }
    return 1;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    
    while (fgets(line, 100, f)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        long long x, y;
        sscanf(line, "%lld,%lld", &x, &y);
        tile_x[num_tiles] = x;
        tile_y[num_tiles] = y;
        num_tiles++;
    }
    fclose(f);
    
    long long total = 0;
    
    for (int i = 0; i < num_tiles; i++) {
        for (int j = i + 1; j < num_tiles; j++) {
            long long x1 = tile_x[i], y1 = tile_y[i];
            long long x2 = tile_x[j], y2 = tile_y[j];
            long long minx = (x1 < x2) ? x1 : x2;
            long long maxx = (x1 > x2) ? x1 : x2;
            long long miny = (y1 < y2) ? y1 : y2;
            long long maxy = (y1 > y2) ? y1 : y2;
            
            long long area = (maxx - minx + 1) * (maxy - miny + 1);
            if (area <= total) continue;
            
            if (rect_valid(minx, miny, maxx, maxy)) {
                total = area;
                printf("tiles (%lld,%lld) and (%lld,%lld) -> area %lld\n", x1, y1, x2, y2, total);
            }
        }
    }
    
    printf("\nfinal sum pt.2: %lld\n", total);
    return 0;
}