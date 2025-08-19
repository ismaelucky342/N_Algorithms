# Binary Search Tree (BST) Data Structure

## Description
A Binary Search Tree is a hierarchical data structure where each node has at most two children, and the left subtree contains values less than the parent node, while the right subtree contains values greater than the parent node.

## BST Properties

### Fundamental Properties
- **Left Subtree**: All values < parent node
- **Right Subtree**: All values > parent node
- **Unique Values**: No duplicate values allowed
- **Recursive Structure**: Each subtree is also a BST

### Time Complexity

| Operation | Average Case | Worst Case | Best Case |
|-----------|--------------|------------|-----------|
| **Search** | O(log n) | O(n) | O(1) |
| **Insert** | O(log n) | O(n) | O(1) |
| **Delete** | O(log n) | O(n) | O(1) |
| **Find Min/Max** | O(log n) | O(n) | O(1) |
| **Traversal** | O(n) | O(n) | O(n) |

### Space Complexity
- **Storage**: O(n) for n nodes
- **Recursion Stack**: O(h) where h is height
- **Average Height**: O(log n)
- **Worst Height**: O(n) - skewed tree

## Features Implemented

### Basic Operations
- **Insert**: Add new nodes maintaining BST property
- **Search**: Find specific values efficiently
- **Delete**: Remove nodes with three cases handling
- **Find Min/Max**: Leftmost/rightmost nodes

### Tree Traversals
- **Inorder**: Left → Root → Right (sorted order)
- **Preorder**: Root → Left → Right (copy tree)
- **Postorder**: Left → Right → Root (delete tree)
- **Level Order**: Breadth-first traversal

### Advanced Operations
- **Height Calculation**: Maximum depth from root
- **Node Counting**: Total number of nodes
- **BST Validation**: Verify tree satisfies BST property
- **Tree Visualization**: Display tree structure

### Specialized Queries
- **Lowest Common Ancestor (LCA)**: Find common parent
- **Range Queries**: Print values in given range
- **Kth Smallest/Largest**: Order statistics
- **Distance Between Nodes**: Path length calculation

## How to Compile and Run

```bash
gcc -o bst bst.c
./bst
```

## Example Usage

```
=== Binary Search Tree Operations ===
Enter your choice: 19
Creating sample tree with values: 50, 30, 70, 20, 40, 60, 80
Sample tree created.

Enter your choice: 13
Tree structure (rotated 90° clockwise):

          80

     70

          60

50

          40

     30

          20

Enter your choice: 6
Inorder traversal: 20 30 40 50 60 70 80
```

## Algorithm Details

### Insertion Algorithm
```c
BSTNode* insert(BSTNode* root, int data) {
    if (root == NULL) {
        return create_node(data);  // Base case
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);   // Go left
    } else if (data > root->data) {
        root->right = insert(root->right, data); // Go right
    }
    // Ignore duplicates
    
    return root;
}
```

### Deletion Cases
1. **Leaf Node**: Simply remove the node
2. **One Child**: Replace node with its child
3. **Two Children**: Replace with inorder successor (or predecessor)

```c
// Case 3: Two children - find inorder successor
BSTNode* temp = find_min(root->right);
root->data = temp->data;
root->right = delete_node(root->right, temp->data);
```

### Search Algorithm
```c
BSTNode* search(BSTNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;  // Found or not found
    }
    
    if (data < root->data) {
        return search(root->left, data);   // Search left
    } else {
        return search(root->right, data);  // Search right
    }
}
```

## Tree Traversals

### Inorder Traversal (LNR)
- **Order**: Left → Node → Right
- **Result**: Sorted sequence
- **Use**: Printing sorted data, validation

### Preorder Traversal (NLR)
- **Order**: Node → Left → Right
- **Result**: Root-first sequence
- **Use**: Tree copying, expression trees

### Postorder Traversal (LRN)
- **Order**: Left → Right → Node
- **Result**: Children-first sequence
- **Use**: Tree deletion, calculating sizes

### Level Order Traversal
- **Order**: Level by level (BFS)
- **Implementation**: Uses queue
- **Use**: Tree printing, shortest paths

## Advanced Algorithms

### Lowest Common Ancestor
```c
BSTNode* lowest_common_ancestor(BSTNode* root, int n1, int n2) {
    if (n1 < root->data && n2 < root->data) {
        return lowest_common_ancestor(root->left, n1, n2);
    }
    if (n1 > root->data && n2 > root->data) {
        return lowest_common_ancestor(root->right, n1, n2);
    }
    return root;  // Split point is LCA
}
```

### Kth Smallest Element
```c
// Inorder traversal with counting
BSTNode* kth_smallest(BSTNode* root, int k, int* count) {
    if (root == NULL) return NULL;
    
    BSTNode* left = kth_smallest(root->left, k, count);
    if (left != NULL) return left;
    
    (*count)++;
    if (*count == k) return root;
    
    return kth_smallest(root->right, k, count);
}
```

## Advantages

### Efficiency
- **Logarithmic Operations**: Average O(log n) for basic operations
- **Sorted Output**: Inorder traversal gives sorted sequence
- **Dynamic Size**: Can grow and shrink efficiently
- **No Memory Waste**: Only allocates needed space

### Flexibility
- **Range Queries**: Efficiently find values in ranges
- **Order Statistics**: Find kth smallest/largest efficiently
- **Predecessor/Successor**: Easy to find adjacent values

## Disadvantages

### Performance Issues
- **Worst Case**: O(n) for skewed trees
- **No Balancing**: Can become unbalanced easily
- **Memory Overhead**: Pointer storage for each node
- **Cache Performance**: Poor spatial locality

### Limitations
- **No Duplicates**: Cannot store duplicate values
- **Sequential Input**: Creates skewed tree
- **No Index Access**: Cannot access by position directly

## Applications

### Database Systems
- **Indexing**: Database index structures
- **Query Optimization**: Range queries
- **Sorted Retrieval**: Maintaining sorted data
- **Transaction Logs**: Ordered event processing

### File Systems
- **Directory Structure**: Hierarchical organization
- **File Indexing**: Quick file lookup
- **Version Control**: Branch management
- **Backup Systems**: Incremental backups

### Compiler Design
- **Symbol Tables**: Variable/function lookup
- **Expression Trees**: Mathematical expressions
- **Syntax Trees**: Parse tree representation
- **Optimization**: Code transformation

### Gaming and AI
- **Decision Trees**: Game AI decisions
- **Pathfinding**: Tree-based algorithms
- **State Spaces**: Game state representation
- **Rule Engines**: Condition evaluation

## BST vs Other Data Structures

| Structure | Search | Insert | Delete | Sorted Output | Memory |
|-----------|--------|---------|--------|---------------|---------|
| **BST** | O(log n) avg | O(log n) avg | O(log n) avg | O(n) | O(n) |
| **Array** | O(n) | O(n) | O(n) | O(n log n) | O(n) |
| **Sorted Array** | O(log n) | O(n) | O(n) | O(1) | O(n) |
| **Hash Table** | O(1) avg | O(1) avg | O(1) avg | O(n log n) | O(n) |
| **Linked List** | O(n) | O(1) | O(n) | O(n log n) | O(n) |

## Optimization Techniques

### Tree Balancing
- **AVL Trees**: Height-balanced BST
- **Red-Black Trees**: Color-based balancing
- **Splay Trees**: Self-adjusting trees
- **Treaps**: Randomized binary search trees

### Memory Optimization
- **Node Pooling**: Preallocate node memory
- **Compact Representation**: Array-based implementation
- **Memory Alignment**: Optimize cache usage

### Performance Optimization
- **Iterative Traversal**: Avoid recursion overhead
- **Bulk Operations**: Batch insertions/deletions
- **Lazy Deletion**: Mark nodes instead of removing

## Common Problems and Solutions

### Skewed Trees
- **Problem**: Sequential insertion creates linked list
- **Solution**: Use self-balancing trees
- **Detection**: Monitor height vs log(n)

### Memory Leaks
- **Problem**: Forgetting to free nodes
- **Solution**: Systematic traversal for cleanup
- **Prevention**: RAII patterns, smart pointers

### Duplicate Handling
- **Problem**: BST doesn't handle duplicates well
- **Solutions**:
  - Count field in nodes
  - Allow duplicates in one subtree
  - Use multiset data structure

## Testing Strategies

### Correctness Testing
1. **Empty Tree**: Operations on empty tree
2. **Single Node**: Root-only operations
3. **Balanced Tree**: Well-balanced input
4. **Skewed Tree**: Sequential input
5. **Random Input**: Various insertion orders

### Performance Testing
1. **Worst Case**: Sequential insertions
2. **Best Case**: Balanced tree operations
3. **Random Operations**: Mixed insert/delete/search
4. **Large Data**: Scalability testing

## Implementation Tips

1. **Handle NULL Pointers**: Always check for NULL
2. **Recursive Base Cases**: Define clear stopping conditions
3. **Memory Management**: Free nodes properly
4. **Error Handling**: Validate input parameters
5. **Debugging**: Implement tree visualization
6. **Testing**: Create comprehensive test cases

## Extensions and Variations

### Variants
- **Threaded BST**: Faster inorder traversal
- **BST with Parent Pointers**: Easier navigation
- **Persistent BST**: Immutable versions
- **Probabilistic BST**: Skip lists

### Applications
- **Interval Trees**: Overlapping intervals
- **Segment Trees**: Range queries
- **Binary Indexed Trees**: Cumulative frequencies
- **Cartesian Trees**: Range minimum queries
