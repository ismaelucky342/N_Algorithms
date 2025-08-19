#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure for queue
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

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

// Queue operations
Queue* create_queue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool is_empty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
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

// BFS traversal from a given starting vertex
void bfs(Graph* graph, int start_vertex) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    Queue* queue = create_queue();
    
    visited[start_vertex] = true;
    enqueue(queue, start_vertex);
    
    printf("BFS traversal starting from vertex %d: ", start_vertex);
    
    while (!is_empty(queue)) {
        int current_vertex = dequeue(queue);
        printf("%d ", current_vertex);
        
        // Get all adjacent vertices of the dequeued vertex
        AdjListNode* temp = graph->array[current_vertex].head;
        while (temp) {
            int adj_vertex = temp->dest;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = true;
                enqueue(queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    
    free(visited);
    free(queue);
}

// BFS to find shortest path between two vertices
bool bfs_shortest_path(Graph* graph, int start, int end) {
    if (start == end) {
        printf("Shortest path from %d to %d: %d\n", start, end, start);
        return true;
    }
    
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    int* parent = malloc(graph->num_vertices * sizeof(int));
    Queue* queue = create_queue();
    
    for (int i = 0; i < graph->num_vertices; i++) {
        parent[i] = -1;
    }
    
    visited[start] = true;
    enqueue(queue, start);
    
    bool found = false;
    
    while (!is_empty(queue) && !found) {
        int current_vertex = dequeue(queue);
        
        AdjListNode* temp = graph->array[current_vertex].head;
        while (temp) {
            int adj_vertex = temp->dest;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = true;
                parent[adj_vertex] = current_vertex;
                enqueue(queue, adj_vertex);
                
                if (adj_vertex == end) {
                    found = true;
                    break;
                }
            }
            temp = temp->next;
        }
    }
    
    if (found) {
        // Reconstruct path
        int path[MAX_VERTICES];
        int path_length = 0;
        int current = end;
        
        while (current != -1) {
            path[path_length++] = current;
            current = parent[current];
        }
        
        printf("Shortest path from %d to %d: ", start, end);
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf(" (Length: %d)\n", path_length - 1);
    } else {
        printf("No path exists from %d to %d\n", start, end);
    }
    
    free(visited);
    free(parent);
    free(queue);
    return found;
}

// Check if graph is connected using BFS
bool is_connected(Graph* graph) {
    bool* visited = calloc(graph->num_vertices, sizeof(bool));
    Queue* queue = create_queue();
    
    // Start BFS from vertex 0
    visited[0] = true;
    enqueue(queue, 0);
    int visited_count = 1;
    
    while (!is_empty(queue)) {
        int current_vertex = dequeue(queue);
        
        AdjListNode* temp = graph->array[current_vertex].head;
        while (temp) {
            int adj_vertex = temp->dest;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = true;
                enqueue(queue, adj_vertex);
                visited_count++;
            }
            temp = temp->next;
        }
    }
    
    bool connected = (visited_count == graph->num_vertices);
    free(visited);
    free(queue);
    return connected;
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
        printf("\n--- BFS Operations ---\n");
        printf("1. BFS Traversal\n");
        printf("2. Find Shortest Path\n");
        printf("3. Check if Graph is Connected\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int start;
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    bfs(graph, start);
                } else {
                    printf("Invalid vertex!\n");
                }
                break;
            }
            case 2: {
                int start, end;
                printf("Enter start and end vertices: ");
                scanf("%d %d", &start, &end);
                if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                    bfs_shortest_path(graph, start, end);
                } else {
                    printf("Invalid vertices!\n");
                }
                break;
            }
            case 3: {
                if (is_connected(graph)) {
                    printf("Graph is connected.\n");
                } else {
                    printf("Graph is not connected.\n");
                }
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 4);
    
    free_graph(graph);
    return 0;
}
