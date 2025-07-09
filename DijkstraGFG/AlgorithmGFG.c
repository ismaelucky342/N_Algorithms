#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

typedef struct s_edge {
	int to;
	int weight;
	struct s_edge *next;
} t_edge;

typedef struct s_graph {
	int num_nodes;
	t_edge *adj[MAX_NODES];
} t_graph;

t_graph *create_graph(int num_nodes) {
	t_graph *g = calloc(1, sizeof(t_graph));
	if (!g) {
		fprintf(stderr, "Memory allocation failed for graph.\n");
		exit(EXIT_FAILURE);
	}
	g->num_nodes = num_nodes;
	return g;
}

void add_edge(t_graph *g, int from, int to, int weight) {
	t_edge *e = malloc(sizeof(t_edge));
	if (!e) {
		fprintf(stderr, "Memory allocation failed for edge.\n");
		exit(EXIT_FAILURE);
	}
	e->to = to;
	e->weight = weight;
	e->next = g->adj[from];
	g->adj[from] = e;
}

void free_graph(t_graph *g) {
	for (int i = 0; i < g->num_nodes; i++) {
		t_edge *e = g->adj[i];
		while (e) {
			t_edge *tmp = e;
			e = e->next;
			free(tmp);
		}
	}
	free(g);
}

void print_distances(int dist[], int n, int start) {
	printf("\nMinimum distances from node %d:\n", start);
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF)
			printf("Node %d: INFINITE\n", i);
		else
			printf("Node %d: %d\n", i, dist[i]);
	}
}

void dijkstra(t_graph *g, int start) {
	int dist[MAX_NODES];
	int visited[MAX_NODES] = {0};

	for (int i = 0; i < g->num_nodes; i++)
		dist[i] = INF;
	dist[start] = 0;

	for (int count = 0; count < g->num_nodes; count++) {
		int u = -1;
		for (int i = 0; i < g->num_nodes; i++)
			if (!visited[i] && (u == -1 || dist[i] < dist[u]))
				u = i;

		if (u == -1 || dist[u] == INF)
			break;

		visited[u] = 1;

		for (t_edge *e = g->adj[u]; e; e = e->next) {
			int v = e->to;
			if (!visited[v] && dist[u] + e->weight < dist[v])
				dist[v] = dist[u] + e->weight;
		}
	}
	print_distances(dist, g->num_nodes, start);
}

int main(void) {
	int n, m;
	printf("Number of nodes: ");
	if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_NODES) {
		fprintf(stderr, "Invalid number of nodes.\n");
		return EXIT_FAILURE;
	}

	printf("Number of edges: ");
	if (scanf("%d", &m) != 1 || m < 0) {
		fprintf(stderr, "Invalid number of edges.\n");
		return EXIT_FAILURE;
	}

	t_graph *g = create_graph(n);

	printf("Enter edges (format: from to weight):\n");
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		if (scanf("%d %d %d", &from, &to, &weight) != 3 ||
			from < 0 || from >= n || to < 0 || to >= n || weight < 0) {
			fprintf(stderr, "Invalid input for edge %d.\n", i + 1);
			i--;
			while (getchar() != '\n'); // clear input buffer
			continue;
		}
		add_edge(g, from, to, weight);
		add_edge(g, to, from, weight); // For undirected graph
	}

	int start;
	printf("Start node: ");
	if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
		fprintf(stderr, "Invalid start node.\n");
		free_graph(g);
		return EXIT_FAILURE;
	}

	dijkstra(g, start);
	free_graph(g);
	return EXIT_SUCCESS;
}
