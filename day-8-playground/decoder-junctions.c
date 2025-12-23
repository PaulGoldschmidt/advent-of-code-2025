// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int x[2000], y[2000], z[2000];
int n = 0;

static int parent[2000];
static int size[2000];

int find(int a) { // path compression
    while (parent[a] != a) {
        parent[a] = parent[parent[a]];
        a = parent[a];
    }
    return a;
}

int unite(int a, int b) { // returns 1 if actually merged
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) return 0;
    if (size[ra] < size[rb]) {
        parent[ra] = rb;
        size[rb] += size[ra];
    } else {
        parent[rb] = ra;
        size[ra] += size[rb];
    }
    return 1;
}

typedef struct {
    double dist;
    int a, b;
} Edge;

static Edge edges[2000000];
int num_edges = 0;

int cmp(const void *p1, const void *p2) {
    Edge *e1 = (Edge *)p1;
    Edge *e2 = (Edge *)p2;
    if (e1->dist < e2->dist) return -1;
    if (e1->dist > e2->dist) return 1;
    return 0;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[100];
    while (fgets(line, 100, f)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        sscanf(line, "%d,%d,%d", &x[n], &y[n], &z[n]);
        n++;
    }
    fclose(f);

    for (int i = 0; i < n; i++) { // init unionfind
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < n; i++) { // all pairs
        for (int j = i + 1; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dz = z[i] - z[j];
            edges[num_edges].dist = sqrt(dx*dx + dy*dy + dz*dz);
            edges[num_edges].a = i;
            edges[num_edges].b = j;
            num_edges++;
        }
    }

    qsort(edges, num_edges, sizeof(Edge), cmp);

    int circuits = n;
    int last_a = 0, last_b = 0;
    for (int i = 0; i < num_edges && circuits > 1; i++) { // connect until one circuit...
        if (unite(edges[i].a, edges[i].b)) {
            circuits--;
            last_a = edges[i].a;
            last_b = edges[i].b;
        }
    }

    long long total = (long long)x[last_a] * (long long)x[last_b];
    printf("\nfinal sum pt.2: %lld\n", total);
    return 0;
}