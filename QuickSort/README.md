# Quick Sort Algorithm

## Description
Quick Sort is a highly efficient divide-and-conquer sorting algorithm. It works by selecting a 'pivot' element and partitioning the array around the pivot.

## Time Complexity
- **Best Case**: O(n log n) - Balanced partitions
- **Average Case**: O(n log n)
- **Worst Case**: O(n²) - When pivot is always smallest/largest

## Space Complexity
- **Average**: O(log n) due to recursion
- **Worst Case**: O(n) for unbalanced recursion

## Variants Implemented

### 1. Standard Quick Sort (Lomuto Partition)
- Simple and easy to understand
- Pivot is always the last element

### 2. Hoare Partition Scheme
- More efficient than Lomuto
- Uses two pointers from both ends
- Fewer swaps on average

### 3. Randomized Quick Sort
- Chooses random pivot to avoid worst case
- Expected time complexity: O(n log n)

## How to Compile and Run

```bash
gcc -o quick_sort quick_sort.c
./quick_sort
```

## Example Usage

```
Enter array size: 8
Enter 8 elements:
64 34 25 12 22 11 90 88

Original array: 64 34 25 12 22 11 90 88 

Choose Quick Sort variant:
1. Standard Quick Sort (Lomuto partition)
2. Quick Sort with Hoare partition
3. Randomized Quick Sort
Enter choice (1-3): 1

Using Standard Quick Sort (Lomuto partition):
Sorted array: 11 12 22 25 34 64 88 90 
Time taken: 0.000015 seconds
```

## Algorithm Steps
1. Choose a pivot element from the array
2. Partition the array so that:
   - Elements smaller than pivot go to the left
   - Elements greater than pivot go to the right
3. Recursively apply the same process to sub-arrays
4. Base case: arrays with 0 or 1 element are already sorted

## Advantages
- In-place sorting (O(log n) extra space)
- Generally faster than other O(n log n) algorithms
- Cache-efficient due to good locality of reference

## Disadvantages
- Worst-case time complexity is O(n²)
- Not stable (doesn't preserve relative order of equal elements)
- Performance depends on pivot selection
