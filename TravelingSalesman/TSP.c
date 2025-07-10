#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int tsp(int **graph, int *visited, int pos, int count, int cost, int start, int N) {
    if (count == N && graph[pos][start]) {
        return cost + graph[pos][start];
    }

    int ans = INT_MAX;
    for (int city = 0; city < N; city++) {
        if (!visited[city] && graph[pos][city]) {
            visited[city] = 1;
            int newCost = tsp(graph, visited, city, count + 1, cost + graph[pos][city], start, N);
            if (newCost < ans)
                ans = newCost;
            visited[city] = 0;
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s N matrix...\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (argc != 2 + N * N) {
        printf("Error: Expected %d matrix elements, got %d.\n", N * N, argc - 2);
        return 1;
    }

    int **graph = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        graph[i] = malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            graph[i][j] = atoi(argv[2 + i * N + j]);
        }
    }

    int *visited = calloc(N, sizeof(int));
    visited[0] = 1;

    int result = tsp(graph, visited, 0, 1, 0, 0, N);
    printf("Minimum TSP cost (brute-force): %d\n", result);

    for (int i = 0; i < N; i++) free(graph[i]);
    free(graph);
    free(visited);

    return 0;
}
