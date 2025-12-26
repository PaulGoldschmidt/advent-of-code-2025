// By Paul G, rewritten in ICE 572 // 2025-12-23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char names[2000][8];
int adj[2000][50], adj_n[2000]; // adjacency list
int rev[2000][50], rev_n[2000];
int n = 0;

int topo[2000], topo_n = 0;
int vis[2000];
long long nums[2000];

int node(char *s) { // create node id
    for (int i = 0; i < n; i++)
        if (strcmp(names[i], s) == 0) return i;
    strcpy(names[n], s);
    adj_n[n] = 0;
    rev_n[n] = 0;
    return n++;
}

void dfs(int u) { // topological sort
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = 0; i < adj_n[u]; i++)
        dfs(adj[u][i]);
    topo[topo_n++] = u;
}

long long get(int src, int tgt) { // count paths src -> tgt
    memset(nums, 0, sizeof(nums));
    nums[src] = 1;
    for (int i = topo_n - 1; i >= 0; i--) {
        int t = topo[i];
        if (t == src) continue;
        for (int j = 0; j < rev_n[t]; j++)
            nums[t] += nums[rev[t][j]];
    }
    return nums[tgt];
}

int topo_idx(int u) { // find index
    for (int i = 0; i < topo_n; i++)
        if (topo[i] == u) return i;
    return -1;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[256];

    int svr = node("svr");
    int out = node("out");
    int dac = node("dac");
    int fft = node("fft");

    while (fgets(line, 256, f)) {
        char *p = strtok(line, ": \n");
        if (!p) continue;
        int src = node(p);
        while ((p = strtok(NULL, " \n"))) {
            int dst = node(p);
            adj[src][adj_n[src]++] = dst;
            rev[dst][rev_n[dst]++] = src;
        }
    }
    fclose(f);

    dfs(svr);

    long long total;
    if (topo_idx(fft) > topo_idx(dac))
        total = get(svr, fft) * get(fft, dac) * get(dac, out);
    else
        total = get(svr, dac) * get(dac, fft) * get(fft, out);
    printf("\nfinal sum pt.2: %lld\n", total);

    return 0;
}