# Binary Search Algorithm

## Description
Binary Search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half.

## Time Complexity
- **Best Case**: O(1) - Element found at middle
- **Average Case**: O(log n)
- **Worst Case**: O(log n)

## Space Complexity
- **Iterative**: O(1)
- **Recursive**: O(log n) due to recursion stack

## How to Compile and Run

```bash
gcc -o binary_search binary_search.c
./binary_search
```

## Example Usage

```
Enter array size: 6
Enter 6 sorted elements:
1 3 5 7 9 11
Array: 1 3 5 7 9 11 
Enter target element to search: 7
Choose search method:
1. Iterative Binary Search
2. Recursive Binary Search
Enter choice (1 or 2): 1
Using Iterative Binary Search:
Element 7 found at index 3
```

## Prerequisites
- Array must be sorted in ascending order
- Elements should be comparable

## Algorithm Steps
1. Compare target with middle element
2. If equal, return the index
3. If target is smaller, search left half
4. If target is larger, search right half
5. Repeat until found or search space is empty
