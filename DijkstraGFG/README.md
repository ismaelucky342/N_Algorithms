# Dijkstra's Algorithm

## Problem Description

Dijkstra's algorithm is used to find the shortest path from a source node to all other nodes in a weighted graph with non-negative edge weights. It is widely used in network routing protocols and mapping applications.

## How Dijkstra's Algorithm Works

1. **Initialization**:  
	- Set the distance to the source node as 0 and to all other nodes as infinity.
	- Mark all nodes as unvisited.
	- Set the source node as the current node.

2. **Main Loop**:  
	- For the current node, consider all its unvisited neighbors and calculate their tentative distances through the current node.
	- If the calculated distance of a node is less than the known distance, update the shortest distance.
	- After considering all neighbors, mark the current node as visited.
	- Select the unvisited node with the smallest tentative distance as the new current node.
	- Repeat until all nodes are visited.

3. **Result**:  
	- The shortest path from the source to every other node is found.

## Implementation in This Repository

This repository contains a C implementation of Dijkstra's algorithm. The main steps are:

- **Graph Representation**:  
  The graph is represented using an adjacency matrix, where `graph[i][j]` holds the weight of the edge from node `i` to node `j`. If there is no edge, the value is set to 0 or a large number (e.g., `INT_MAX`).

- **Algorithm Steps**:  
  - An array `dist[]` stores the shortest distance from the source to each node.
  - A boolean array `visited[]` keeps track of visited nodes.
  - The algorithm iteratively selects the unvisited node with the smallest distance, updates its neighbors, and marks it as visited.

- **Output**:  
  The program prints the shortest distances from the source node to all other nodes.

## Example

Given the following graph:

```
		(0)
	  /   \
	4/     \1
	/       \
 (1)------(2)
	  2
```

The algorithm will output the shortest distances from the source node to all other nodes.

## Usage

1. Clone the repository.
2. Compile the code using a C compiler:
	```
	gcc dijkstra.c -o dijkstra
	```
3. Run the executable:
	```
	./dijkstra
	```

You can modify the adjacency matrix in the code to test different graphs.
