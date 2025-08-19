# Merge Sort Algorithm

## Description
Merge Sort is a stable, divide-and-conquer sorting algorithm that divides the array into halves, sorts them separately, and then merges them back together.

## Time Complexity
- **Best Case**: O(n log n)
- **Average Case**: O(n log n)
- **Worst Case**: O(n log n)

## Space Complexity
- **Recursive**: O(n) for temporary arrays + O(log n) for recursion stack
- **Iterative**: O(n) for temporary arrays only

## Variants Implemented

### 1. Recursive Merge Sort
- Classic divide-and-conquer approach
- Easy to understand and implement
- Uses recursion stack

### 2. Iterative Merge Sort
- Bottom-up approach
- No recursion overhead
- Better space efficiency

## How to Compile and Run

```bash
gcc -o merge_sort merge_sort.c
./merge_sort
```

## Example Usage

```
Enter array size: 8
Choose input method:
1. Manual input
2. Random generation
Enter choice (1-2): 1
Enter 8 elements:
64 34 25 12 22 11 90 88

Original array: 64 34 25 12 22 11 90 88 

Choose Merge Sort variant:
1. Recursive Merge Sort
2. Iterative Merge Sort
3. Compare both methods
Enter choice (1-3): 3

Comparison Results:
Recursive Merge Sort time: 0.000012 seconds
Iterative Merge Sort time: 0.000008 seconds
Sorted array: 11 12 22 25 34 64 88 90 
```

## Algorithm Steps (Recursive)
1. **Divide**: Split the array into two halves
2. **Conquer**: Recursively sort both halves
3. **Combine**: Merge the two sorted halves

## Algorithm Steps (Iterative)
1. Start with subarrays of size 1
2. Merge adjacent subarrays
3. Double the subarray size and repeat
4. Continue until entire array is sorted

## Advantages
- **Stable**: Maintains relative order of equal elements
- **Predictable**: Always O(n log n) time complexity
- **Good for linked lists**: No random access needed
- **External sorting**: Works well for large datasets

## Disadvantages
- **Space complexity**: Requires O(n) extra space
- **Not in-place**: Cannot sort with constant extra space
- **Overhead**: More overhead than Quick Sort for small arrays

## Best Use Cases
- When stability is required
- When guaranteed O(n log n) performance is needed
- For sorting linked lists
- External sorting of large files
