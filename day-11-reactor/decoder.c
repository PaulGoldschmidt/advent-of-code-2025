#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char names[2000][8];
int adj[2000][20], adj_n[2000]; // adjacencie list
long long memo[2000];
int n = 0;

int node(char *s) { //create node id
    for (int i = 0; i < n; i++)
        if (strcmp(names[i], s) == 0) return i;
    strcpy(names[n], s);
    memo[n] = -1;
    adj_n[n] = 0;
    return n++;
}

long long paths(int u, int t) { // count paths
    if (u == t) return 1;
    if (memo[u] >= 0) return memo[u];
    memo[u] = 0;
    for (int i = 0; i < adj_n[u]; i++)
        memo[u] += paths(adj[u][i], t);
    return memo[u];
}

int main() {
    FILE *f = fopen("input.txt", "r");
    char line[256];
    
    while (fgets(line, 256, f)) {
        char *p = strtok(line, ": \n");
        int src = node(p);
        while ((p = strtok(NULL, " \n")))
            adj[src][adj_n[src]++] = node(p);
    }
    fclose(f);
    
    int total = paths(node("you"), node("out"));
    printf("\nfinal sum: %d\n", total);
    return 0;
}