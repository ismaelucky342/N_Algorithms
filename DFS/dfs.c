#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure for adjacency list node
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure for adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Structure for graph
typedef struct Graph {
    int num_vertices;
    AdjList* array;
} Graph;

// Stack for iterative DFS
typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

// Stack operations
Stack* create_stack() {
    Stack* s = malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

bool is_stack_empty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (s->top == MAX_VERTICES - 1) {
        printf("Stack overflow!\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(Stack* s) {
    if (is_stack_empty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->items[s->top--];
}

// Create a new adjacency list node
AdjListNode* new_adj_list_node(int dest) {
    AdjListNode* new_node = malloc(sizeof(AdjListNode));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

// Create a graph with given number of vertices
Graph* create_graph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    graph->array = malloc(vertices * sizeof(AdjList));
    
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Add an edge to undirected graph
void add_edge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    AdjListNode* new_node = new_adj_list_node(dest);
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;
    
    // Add edge from dest to src (undirected graph)
    new_node = new_adj_list_node(src);
    new_node->next = graph->array[dest].head;
    graph->array[dest].head = new_node;
}

// Recursive DFS utility function
void dfs_recursive_util(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);
    
    // Recur for all adjacent vertices
    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        if (!visited[temp->dest]) {
            dfs_recursive_util(graph, temp->dest, visited);
        }
        temp = temp->next;
    }
}

// Recursive DFS traversal
void dfs_recursive(Graph* graph, int start_vertex) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    
    printf("DFS traversal (Recursive) starting from vertex %d: ", start_vertex);
    dfs_recursive_util(graph, start_vertex, visited);
    printf("\n");
    
    free(visited);
}

// Iterative DFS traversal
void dfs_iterative(Graph* graph, int start_vertex) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    Stack* stack = create_stack();
    
    push(stack, start_vertex);
    
    printf("DFS traversal (Iterative) starting from vertex %d: ", start_vertex);
    
    while (!is_stack_empty(stack)) {
        int vertex = pop(stack);
        
        if (!visited[vertex]) {
            visited[vertex] = true;
            printf("%d ", vertex);
            
            // Add all adjacent vertices to stack (in reverse order for consistency)
            AdjListNode* temp = graph->array[vertex].head;
            int adj_vertices[MAX_VERTICES];
            int count = 0;
            
            while (temp) {
                if (!visited[temp->dest]) {
                    adj_vertices[count++] = temp->dest;
                }
                temp = temp->next;
            }
            
            // Push in reverse order to maintain left-to-right traversal
            for (int i = count - 1; i >= 0; i--) {
                push(stack, adj_vertices[i]);
            }
        }
    }
    printf("\n");
    
    free(visited);
    free(stack);
}

// DFS to find path between two vertices
bool dfs_find_path(Graph* graph, int start, int end, bool* visited, int* path, int* path_index) {
    visited[start] = true;
    path[(*path_index)++] = start;
    
    if (start == end) {
        return true;
    }
    
    AdjListNode* temp = graph->array[start].head;
    while (temp) {
        if (!visited[temp->dest]) {
            if (dfs_find_path(graph, temp->dest, end, visited, path, path_index)) {
                return true;
            }
        }
        temp = temp->next;
    }
    
    // Backtrack
    (*path_index)--;
    return false;
}

// Find path using DFS
void find_path_dfs(Graph* graph, int start, int end) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int path[MAX_VERTICES];
    int path_index = 0;
    
    if (dfs_find_path(graph, start, end, visited, path, &path_index)) {
        printf("Path from %d to %d: ", start, end);
        for (int i = 0; i < path_index; i++) {
            printf("%d", path[i]);
            if (i < path_index - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("No path exists from %d to %d\n", start, end);
    }
    
    free(visited);
}

// DFS to detect cycle in undirected graph
bool has_cycle_util(Graph* graph, int vertex, bool* visited, int parent) {
    visited[vertex] = true;
    
    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        int adj_vertex = temp->dest;
        
        if (!visited[adj_vertex]) {
            if (has_cycle_util(graph, adj_vertex, visited, vertex)) {
                return true;
            }
        } else if (adj_vertex != parent) {
            return true; // Back edge found (cycle detected)
        }
        temp = temp->next;
    }
    
    return false;
}

// Check if graph has cycle
bool has_cycle(Graph* graph) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    
    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            if (has_cycle_util(graph, i, visited, -1)) {
                free(visited);
                return true;
            }
        }
    }
    
    free(visited);
    return false;
}

// Count connected components using DFS
int count_connected_components(Graph* graph) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int components = 0;
    
    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            dfs_recursive_util(graph, i, visited);
            components++;
        }
    }
    
    free(visited);
    return components;
}

// Topological sort using DFS (for directed acyclic graphs)
void topological_sort_util(Graph* graph, int vertex, bool* visited, Stack* stack) {
    visited[vertex] = true;
    
    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        if (!visited[temp->dest]) {
            topological_sort_util(graph, temp->dest, visited, stack);
        }
        temp = temp->next;
    }
    
    push(stack, vertex);
}

void topological_sort(Graph* graph) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    Stack* stack = create_stack();
    
    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            topological_sort_util(graph, i, visited, stack);
        }
    }
    
    printf("Topological Sort: ");
    while (!is_stack_empty(stack)) {
        printf("%d ", pop(stack));
    }
    printf("\n");
    
    free(visited);
    free(stack);
}

// Print the graph
void print_graph(Graph* graph) {
    printf("\nGraph adjacency list representation:\n");
    for (int v = 0; v < graph->num_vertices; v++) {
        printf("Vertex %d: ", v);
        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            printf("%d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Free graph memory
void free_graph(Graph* graph) {
    for (int v = 0; v < graph->num_vertices; v++) {
        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            AdjListNode* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    int vertices, edges;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return 1;
    }
    
    Graph* graph = create_graph(vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (format: src dest):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            printf("Invalid edge! Skipping...\n");
            i--;
            continue;
        }
        
        add_edge(graph, src, dest);
    }
    
    print_graph(graph);
    
    int choice;
    do {
        printf("\n--- DFS Operations ---\n");
        printf("1. DFS Traversal (Recursive)\n");
        printf("2. DFS Traversal (Iterative)\n");
        printf("3. Find Path between vertices\n");
        printf("4. Check for Cycle\n");
        printf("5. Count Connected Components\n");
        printf("6. Topological Sort\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int start;
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    dfs_recursive(graph, start);
                } else {
                    printf("Invalid vertex!\n");
                }
                break;
            }
            case 2: {
                int start;
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    dfs_iterative(graph, start);
                } else {
                    printf("Invalid vertex!\n");
                }
                break;
            }
            case 3: {
                int start, end;
                printf("Enter start and end vertices: ");
                scanf("%d %d", &start, &end);
                if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                    find_path_dfs(graph, start, end);
                } else {
                    printf("Invalid vertices!\n");
                }
                break;
            }
            case 4: {
                if (has_cycle(graph)) {
                    printf("Graph contains a cycle.\n");
                } else {
                    printf("Graph does not contain a cycle.\n");
                }
                break;
            }
            case 5: {
                printf("Number of connected components: %d\n", count_connected_components(graph));
                break;
            }
            case 6: {
                printf("Note: Topological sort is meaningful for directed acyclic graphs.\n");
                topological_sort(graph);
                break;
            }
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 7);
    
    free_graph(graph);
    return 0;
}
