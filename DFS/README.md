# Depth-First Search (DFS) Algorithm

## Description
Depth-First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It can be implemented using recursion or an explicit stack.

## Time Complexity
- **Time**: O(V + E) where V is vertices and E is edges
- **Space**: O(V) for the recursion stack or explicit stack

## Applications
- **Path Finding**: Find any path between two vertices
- **Cycle Detection**: Detect cycles in graphs
- **Topological Sorting**: Order vertices in directed acyclic graphs
- **Connected Components**: Find all connected components
- **Maze Solving**: Navigate through mazes
- **Puzzle Solving**: Solve puzzles with backtracking

## Features Implemented

### 1. Recursive DFS
- Classic implementation using recursion
- Natural and easy to understand
- Uses system call stack

### 2. Iterative DFS
- Uses explicit stack data structure
- Avoids recursion stack overflow
- More control over traversal

### 3. Path Finding
- Finds any path between two vertices
- Uses backtracking to build path
- Shows complete path when found

### 4. Cycle Detection
- Detects cycles in undirected graphs
- Uses parent tracking to avoid false positives
- Returns boolean result

### 5. Connected Components
- Counts number of connected components
- Useful for graph analysis
- Uses DFS on unvisited vertices

### 6. Topological Sort
- Orders vertices in directed acyclic graphs
- Useful for dependency resolution
- Uses post-order traversal

## How to Compile and Run

```bash
gcc -o dfs dfs.c
./dfs
```

## Example Usage

```
Enter number of vertices: 6
Enter number of edges: 7
Enter edges (format: src dest):
0 1
0 2
1 3
2 4
3 5
4 5
1 4

Graph adjacency list representation:
Vertex 0: 2 1 
Vertex 1: 4 3 0 
Vertex 2: 4 0 
Vertex 3: 5 1 
Vertex 4: 5 2 1 
Vertex 5: 4 3 

--- DFS Operations ---
1. DFS Traversal (Recursive)
2. DFS Traversal (Iterative)
3. Find Path between vertices
4. Check for Cycle
5. Count Connected Components
6. Topological Sort
7. Exit
Enter your choice: 1
Enter starting vertex for DFS: 0
DFS traversal (Recursive) starting from vertex 0: 0 2 4 5 3 1 
```

## Algorithm Steps (Recursive)
1. **Mark** current vertex as visited
2. **Process** current vertex
3. **Recur** for all unvisited adjacent vertices
4. **Backtrack** when no more unvisited neighbors

## Algorithm Steps (Iterative)
1. **Initialize** stack with starting vertex
2. **Pop** vertex from stack
3. **Process** if not visited and mark as visited
4. **Push** all unvisited neighbors to stack
5. **Repeat** until stack is empty

## Data Structures Used
- **Adjacency List**: Efficient graph representation
- **Stack**: LIFO structure for DFS traversal
- **Boolean Array**: Track visited vertices
- **Recursion Stack**: For recursive implementation

## Advantages
- **Memory Efficient**: Uses less memory than BFS for deep graphs
- **Path Finding**: Can find paths (not necessarily shortest)
- **Cycle Detection**: Efficient cycle detection
- **Simplicity**: Simple recursive implementation

## Disadvantages
- **No Shortest Path**: Doesn't guarantee shortest path
- **Stack Overflow**: Recursive version can cause stack overflow
- **Infinite Loops**: Can get stuck in infinite loops without visited tracking

## Comparison with BFS
| Aspect | DFS | BFS |
|--------|-----|-----|
| Data Structure | Stack/Recursion | Queue |
| Memory Usage | O(h) where h is height | O(w) where w is width |
| Shortest Path | No | Yes (unweighted) |
| Implementation | Recursive/Iterative | Iterative |
| Use Cases | Topological sort, cycle detection | Shortest path, level order |

## Applications in Detail

### Cycle Detection
- **Undirected Graphs**: Uses parent tracking
- **Directed Graphs**: Uses three colors (white, gray, black)
- **Time Complexity**: O(V + E)

### Topological Sort
- **Only for DAGs**: Directed Acyclic Graphs
- **Post-order**: Finish times determine order
- **Applications**: Task scheduling, dependency resolution

### Connected Components
- **Undirected Graphs**: Count separate components
- **Applications**: Network analysis, clustering
