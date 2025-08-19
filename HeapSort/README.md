# Heap Sort and Binary Heap Data Structure

## Description
Heap Sort is a comparison-based sorting algorithm that uses a binary heap data structure. A binary heap is a complete binary tree that satisfies the heap property.

## Heap Types

### Max Heap
- **Property**: Parent node ≥ all children nodes
- **Root**: Contains the maximum element
- **Use**: Heap sort (ascending order), priority queues

### Min Heap
- **Property**: Parent node ≤ all children nodes  
- **Root**: Contains the minimum element
- **Use**: Heap sort (descending order), shortest path algorithms

## Time Complexity

| Operation | Time Complexity |
|-----------|----------------|
| **Heap Sort** | O(n log n) |
| **Build Heap** | O(n) |
| **Insert** | O(log n) |
| **Extract Max/Min** | O(log n) |
| **Get Max/Min** | O(1) |
| **Increase/Decrease Key** | O(log n) |
| **Delete** | O(log n) |
| **Heapify** | O(log n) |

## Space Complexity
- **In-place Heap Sort**: O(1) auxiliary space
- **Heap Data Structure**: O(n) for storing elements

## Features Implemented

### Heap Sort Algorithms
- **Ascending Sort**: Using max heap
- **Descending Sort**: Using min heap
- **Performance Timing**: Measure sorting time
- **Random Array Generation**: For testing

### Max Heap Operations
- **Insert**: Add new element maintaining heap property
- **Extract Maximum**: Remove and return largest element
- **Get Maximum**: Return largest element without removing
- **Increase Key**: Increase value at given index
- **Delete Key**: Remove element at given index

### Min Heap Operations
- **Insert**: Add new element maintaining heap property
- **Extract Minimum**: Remove and return smallest element
- **Get Minimum**: Return smallest element without removing
- **Decrease Key**: Decrease value at given index

### Utility Functions
- **Build Heap**: Convert array to heap in O(n) time
- **Heap Validation**: Check if array satisfies heap property
- **Heap Visualization**: Display heap as tree structure
- **Heapify**: Maintain heap property after modification

## How to Compile and Run

```bash
gcc -o heap_sort heap_sort.c
./heap_sort
```

## Example Usage

```
=== Heap Sort and Binary Heap Operations ===
HEAP SORT:
1. Heap Sort (Ascending)
2. Heap Sort (Descending)

Enter your choice: 1
Enter array size: 6
Choose input method:
1. Manual
2. Random
Choice: 1
Enter 6 elements: 64 34 25 12 22 11

Original array: 64 34 25 12 22 11 
Sorted array (ascending): 11 12 22 25 34 64 
Time taken: 0.000023 seconds
```

## Algorithm Details

### Heap Sort Steps
1. **Build Max Heap**: Convert input array to max heap
2. **Extract Elements**: Repeatedly remove max element and place at end
3. **Maintain Heap**: Heapify remaining elements
4. **Result**: Sorted array in ascending order

### Heapify Process
```c
// Max Heapify - ensure parent ≥ children
void max_heapify(int arr[], int n, int i) {
    int largest = i;          // Root
    int left = 2 * i + 1;     // Left child
    int right = 2 * i + 2;    // Right child
    
    // Find largest among root and children
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root, swap and recursively heapify
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest);
    }
}
```

### Build Heap Process
```c
// Build heap from bottom-up
void build_max_heap(int arr[], int n) {
    // Start from last internal node
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(arr, n, i);
    }
}
```

## Heap Properties

### Complete Binary Tree
- **All levels filled** except possibly the last
- **Last level filled** from left to right
- **Array representation**: Easy indexing
  - Parent of node i: `(i-1)/2`
  - Left child of node i: `2*i + 1`
  - Right child of node i: `2*i + 2`

### Heap Property
- **Max Heap**: `arr[parent] ≥ arr[child]`
- **Min Heap**: `arr[parent] ≤ arr[child]`

## Advantages

### Heap Sort
- **Guaranteed Performance**: Always O(n log n)
- **In-place**: Requires only O(1) extra space
- **Not Stable**: Doesn't preserve relative order (can be made stable)
- **No Worst Case**: Consistent performance regardless of input

### Binary Heap
- **Efficient Priority Queue**: Fast insert/extract operations
- **Simple Implementation**: Array-based, easy to code
- **Space Efficient**: Complete tree structure
- **Cache Friendly**: Good locality of reference

## Disadvantages

### Heap Sort
- **Not Stable**: Equal elements may be reordered
- **Poor Cache Performance**: Heap operations access distant memory locations
- **Slower than Quick Sort**: In practice, often slower than well-implemented quick sort

### Binary Heap
- **No Search**: Cannot efficiently search for arbitrary elements
- **Fixed Structure**: Must maintain complete tree property
- **Limited Operations**: Fewer operations compared to balanced BSTs

## Real-World Applications

### Heap Sort
- **External Sorting**: When memory is limited
- **Real-time Systems**: Guaranteed time bounds
- **Embedded Systems**: Predictable performance
- **Database Systems**: Index sorting

### Binary Heap
- **Priority Queues**: Task scheduling, event simulation
- **Dijkstra's Algorithm**: Shortest path finding
- **Huffman Coding**: Data compression
- **Operating Systems**: Process scheduling
- **Graph Algorithms**: Prim's MST, A* search

## Heap vs Other Data Structures

| Feature | Binary Heap | Binary Search Tree | Array |
|---------|------------|-------------------|-------|
| Insert | O(log n) | O(log n) avg | O(1) end, O(n) middle |
| Delete | O(log n) | O(log n) avg | O(1) end, O(n) middle |
| Find Min/Max | O(1) | O(log n) | O(n) unsorted, O(1) sorted |
| Search | O(n) | O(log n) avg | O(n) unsorted, O(log n) sorted |
| Space | O(n) | O(n) | O(n) |

## Implementation Tips

### Heap Operations
1. **Always maintain heap property** after modifications
2. **Use 0-based indexing** for array representation
3. **Handle edge cases**: Empty heap, single element
4. **Efficient build heap**: Use bottom-up approach O(n)

### Memory Management
1. **Dynamic allocation** for variable size heaps
2. **Check capacity** before insertion
3. **Free memory** properly to avoid leaks

### Optimization
1. **Iterative heapify** can be more efficient than recursive
2. **Cache-aware implementations** for better performance
3. **Hybrid approaches** (heap + insertion sort for small arrays)

## Variants and Extensions

### Heap Variants
- **d-ary Heap**: Each node has d children
- **Fibonacci Heap**: Better amortized complexity
- **Binomial Heap**: Mergeable heap
- **Leftist Heap**: Efficient merging

### Applications
- **Top-K Problems**: Find K largest/smallest elements
- **Median Finding**: Using two heaps
- **Graph Algorithms**: Priority-first search
- **Data Streams**: Online algorithms
