# Breadth-First Search (BFS) Algorithm

## Description
Breadth-First Search is a graph traversal algorithm that explores all vertices at the current depth before moving to vertices at the next depth level. It uses a queue data structure.

## Time Complexity
- **Time**: O(V + E) where V is vertices and E is edges
- **Space**: O(V) for the queue and visited array

## Applications
- **Shortest Path**: Find shortest path in unweighted graphs
- **Level Order Traversal**: Traverse graph level by level
- **Connected Components**: Check if graph is connected
- **Web Crawling**: Explore web pages level by level
- **Social Networks**: Find connections within degrees of separation

## Features Implemented

### 1. Basic BFS Traversal
- Explores all reachable vertices from a starting point
- Visits vertices level by level

### 2. Shortest Path Finding
- Finds shortest path between two vertices
- Works for unweighted graphs
- Returns actual path, not just distance

### 3. Connectivity Check
- Determines if the entire graph is connected
- Uses BFS to count reachable vertices

## How to Compile and Run

```bash
gcc -o bfs bfs.c
./bfs
```

## Example Usage

```
Enter number of vertices: 5
Enter number of edges: 6
Enter edges (format: src dest):
0 1
0 2
1 3
2 3
3 4
1 4

Graph adjacency list representation:
Vertex 0: 2 1 
Vertex 1: 4 3 0 
Vertex 2: 3 0 
Vertex 3: 4 2 1 
Vertex 4: 3 1 

--- BFS Operations ---
1. BFS Traversal
2. Find Shortest Path
3. Check if Graph is Connected
4. Exit
Enter your choice: 1
Enter starting vertex for BFS: 0
BFS traversal starting from vertex 0: 0 2 1 3 4 
```

## Algorithm Steps
1. **Initialize**: Create a queue and mark starting vertex as visited
2. **Enqueue**: Add starting vertex to queue
3. **Process**: While queue is not empty:
   - Dequeue a vertex
   - Visit all unvisited adjacent vertices
   - Mark them as visited and enqueue them
4. **Repeat**: Continue until queue is empty

## Data Structures Used
- **Adjacency List**: Efficient graph representation
- **Queue**: FIFO structure for BFS traversal
- **Boolean Array**: Track visited vertices
- **Parent Array**: Reconstruct shortest paths

## Advantages
- **Optimal**: Finds shortest path in unweighted graphs
- **Complete**: Explores all reachable vertices
- **Memory Efficient**: Uses adjacency list representation

## Disadvantages
- **Memory Usage**: Can use significant memory for wide graphs
- **Unweighted Only**: Doesn't handle edge weights
- **Queue Overhead**: Queue operations add some overhead

## Comparison with DFS
| Aspect | BFS | DFS |
|--------|-----|-----|
| Data Structure | Queue | Stack/Recursion |
| Memory | O(V) | O(V) |
| Shortest Path | Yes (unweighted) | No |
| Implementation | Iterative | Recursive/Iterative |
