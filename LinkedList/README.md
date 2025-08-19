# Linked List Data Structure

## Description
A linked list is a linear data structure where elements are stored in nodes, and each node contains data and a reference (or link) to the next node in the sequence.

## Types Implemented

### 1. Singly Linked List
- Each node points to the next node
- Traversal only in forward direction
- Memory efficient (one pointer per node)

### 2. Doubly Linked List
- Each node has pointers to both next and previous nodes
- Bidirectional traversal
- More memory overhead but more flexible

## Time Complexity

| Operation | Singly Linked List | Doubly Linked List |
|-----------|-------------------|-------------------|
| Insert at beginning | O(1) | O(1) |
| Insert at end | O(n) | O(n) |
| Insert at position | O(n) | O(n) |
| Delete by value | O(n) | O(n) |
| Delete at position | O(n) | O(n) |
| Search | O(n) | O(n) |
| Reverse | O(n) | O(n) |

## Space Complexity
- **Singly Linked List**: O(n) - one pointer per node
- **Doubly Linked List**: O(n) - two pointers per node

## Features Implemented

### Basic Operations
- **Insert**: At beginning, end, or specific position
- **Delete**: By value or at specific position
- **Search**: Find element and return position
- **Display**: Show list contents
- **Length**: Count number of elements

### Advanced Operations
- **Reverse**: Reverse the entire list
- **Find Middle**: Using Floyd's tortoise and hare algorithm
- **Remove Duplicates**: From sorted linked list
- **Cycle Detection**: Using Floyd's algorithm
- **Merge**: Merge two sorted linked lists

### Doubly Linked List Specific
- **Bidirectional Display**: Forward and backward traversal
- **Efficient Deletion**: No need to traverse to find previous node

## How to Compile and Run

```bash
gcc -o linked_list linked_list.c
./linked_list
```

## Example Usage

```
=== Linked List Operations ===
SINGLY LINKED LIST:
1. Insert at beginning
2. Insert at end
3. Insert at position
[... more options ...]

Enter your choice: 1
Enter data: 10
Inserted 10 at the beginning.

Enter your choice: 2
Enter data: 20
Inserted 20 at the end.

Enter your choice: 8
List: 10 -> 20 -> NULL
```

## Algorithm Details

### Floyd's Cycle Detection (Tortoise and Hare)
```c
// Two pointers: slow moves one step, fast moves two steps
// If there's a cycle, they will eventually meet
while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return 1; // Cycle found
}
```

### Finding Middle Element
```c
// Slow pointer moves one step, fast moves two steps
// When fast reaches end, slow is at middle
while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
}
return slow; // Middle element
```

### Reversing Linked List
```c
// Three pointers: prev, current, next
// Reverse the direction of links
while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
}
head = prev; // New head
```

## Advantages

### Singly Linked List
- **Dynamic Size**: Can grow/shrink during runtime
- **Memory Efficient**: No wasted memory
- **Easy Insertion/Deletion**: At beginning is O(1)
- **No Memory Preallocation**: Allocate as needed

### Doubly Linked List
- **Bidirectional Traversal**: Can move forward and backward
- **Efficient Deletion**: No need to find previous node
- **Better for Certain Algorithms**: Like LRU cache implementation

## Disadvantages

### Singly Linked List
- **No Random Access**: Must traverse from head
- **No Backward Traversal**: Can only go forward
- **Extra Memory**: Pointer overhead
- **Cache Performance**: Poor spatial locality

### Doubly Linked List
- **More Memory**: Two pointers per node
- **Complex Operations**: More pointers to maintain
- **Higher Overhead**: More complex insertion/deletion

## Real-World Applications

### Singly Linked List
- **Undo Functionality**: In text editors
- **Music Playlist**: Next song functionality
- **Browser History**: Forward navigation
- **Stack Implementation**: Using linked nodes

### Doubly Linked List
- **LRU Cache**: Least Recently Used cache implementation
- **Browser History**: Forward and backward navigation
- **Undo/Redo**: In applications like Photoshop
- **Deque Implementation**: Double-ended queue

## Memory Management

### Best Practices
- **Always Free Memory**: Prevent memory leaks
- **Check Allocation**: Handle malloc failures
- **Initialize Pointers**: Set to NULL after freeing
- **Avoid Dangling Pointers**: Update all references

### Memory Layout
```
Singly:  [Data|Next] -> [Data|Next] -> [Data|NULL]
Doubly:  [Prev|Data|Next] <-> [Prev|Data|Next] <-> [Prev|Data|NULL]
```

## Comparison with Arrays

| Aspect | Linked List | Array |
|--------|-------------|--------|
| Memory | Dynamic | Fixed (static arrays) |
| Access Time | O(n) | O(1) |
| Insert/Delete | O(1) at known position | O(n) in middle |
| Memory Overhead | Extra pointer space | No overhead |
| Cache Performance | Poor | Good |

## When to Use

### Use Linked Lists When:
- Frequent insertions/deletions at the beginning
- Size varies significantly during runtime
- Don't need random access to elements
- Implementing other data structures (stacks, queues)

### Use Arrays When:
- Need random access to elements
- Performing many index-based operations
- Memory usage is critical
- Need better cache performance

## Implementation Tips

1. **Always check for NULL pointers** before dereferencing
2. **Update all relevant pointers** during insertion/deletion
3. **Handle edge cases**: Empty list, single element, etc.
4. **Free memory properly** to avoid memory leaks
5. **Use dummy nodes** to simplify edge case handling (optional)
6. **Draw diagrams** when implementing complex operations
