# Longest Common Subsequence (LCS) Algorithm

## Description
The Longest Common Subsequence (LCS) problem finds the longest subsequence common to two sequences. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

## Problem Definition
Given two strings `X` and `Y`, find the length of their longest common subsequence.

**Example:**
- String 1: "ABCDGH"
- String 2: "AEDFHR"
- LCS: "ADH" (length = 3)

## Time & Space Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| **Recursive** | O(2^(m+n)) | O(m+n) |
| **Memoization** | O(m×n) | O(m×n) |
| **Dynamic Programming** | O(m×n) | O(m×n) |
| **Space Optimized** | O(m×n) | O(min(m,n)) |

Where `m` and `n` are the lengths of the two strings.

## Algorithms Implemented

### 1. Recursive Solution
- **Pure recursion** with overlapping subproblems
- **Exponential time** - only suitable for very small inputs
- **Educational purpose** to understand the problem structure

### 2. Memoization (Top-Down DP)
- **Recursive with caching** of computed results
- **Optimal substructure** with memoization table
- **Better than recursive** but still uses recursion stack

### 3. Dynamic Programming (Bottom-Up)
- **Iterative approach** building solution from smaller problems
- **2D DP table** storing intermediate results
- **Most commonly used** approach

### 4. Space Optimized
- **Reduced space complexity** to O(min(m,n))
- **Only current and previous row** needed
- **Same time complexity** but better space usage

## Features Implemented

### Core LCS Operations
- **Length Calculation**: Find LCS length using different approaches
- **Actual LCS**: Reconstruct and print the actual subsequence
- **DP Table Visualization**: Display the computation table
- **Performance Comparison**: Compare all algorithm variants

### Related Problems
- **Edit Distance**: Levenshtein distance calculation
- **Longest Palindromic Subsequence**: Using LCS with reversed string
- **Diff Algorithm**: Simple version of file difference detection
- **Backtracking**: Reconstruct the actual LCS string

### Utility Features
- **Predefined Test Cases**: Common examples for testing
- **Performance Timing**: Measure execution time
- **Input Validation**: Handle edge cases
- **Memory Management**: Proper allocation and deallocation

## How to Compile and Run

```bash
gcc -o lcs lcs.c
./lcs
```

## Example Usage

```
=== Longest Common Subsequence (LCS) ===
1. Calculate LCS length (DP)
2. Print actual LCS
3. Show DP table

Enter your choice: 2
Enter first string: AGGTAB
Enter second string: GXTXAYB
LCS: "GTAB" (Length: 4)
```

## Algorithm Details

### Dynamic Programming Recurrence
```
LCS[i][j] = {
    0                           if i = 0 or j = 0
    LCS[i-1][j-1] + 1          if X[i-1] = Y[j-1]
    max(LCS[i-1][j], LCS[i][j-1])  otherwise
}
```

### DP Table Example
For strings "ABCDGH" and "AEDFHR":
```
    ε A E D F H R
ε   0 0 0 0 0 0 0
A   0 1 1 1 1 1 1
B   0 1 1 1 1 1 1
C   0 1 1 1 1 1 1
D   0 1 1 2 2 2 2
G   0 1 1 2 2 2 2
H   0 1 1 2 2 3 3
```

### Backtracking for Actual LCS
```c
// Start from bottom-right and trace back
while (i > 0 && j > 0) {
    if (str1[i-1] == str2[j-1]) {
        lcs[index--] = str1[i-1];  // Part of LCS
        i--; j--;
    } else if (dp[i-1][j] > dp[i][j-1]) {
        i--;  // Move up
    } else {
        j--;  // Move left
    }
}
```

## Applications

### Software Development
- **Version Control**: Git diff algorithms
- **Code Comparison**: IDE difference tools
- **File Synchronization**: Backup and sync tools
- **Plagiarism Detection**: Document similarity

### Bioinformatics
- **DNA Sequence Alignment**: Finding common genetic patterns
- **Protein Comparison**: Structural similarity analysis
- **Evolutionary Biology**: Species relationship analysis

### Text Processing
- **Spell Checkers**: Suggesting corrections
- **Data Deduplication**: Finding similar records
- **Text Mining**: Document comparison
- **Translation Tools**: Finding equivalent phrases

### Data Analysis
- **Time Series**: Finding common patterns
- **Log Analysis**: Identifying similar events
- **Recommendation Systems**: User behavior patterns

## Optimization Techniques

### Space Optimization
```c
// Use only two rows instead of full table
int *prev = calloc(n + 1, sizeof(int));
int *curr = calloc(n + 1, sizeof(int));
```

### Practical Optimizations
1. **Early Termination**: Stop if no improvement possible
2. **Preprocessing**: Remove common prefixes/suffixes
3. **Character Frequency**: Skip if character not in other string
4. **Rolling Hash**: For very long strings

## Variants and Extensions

### LCS Variations
- **K-LCS**: Longest common subsequence of K strings
- **Weighted LCS**: Characters have different weights
- **Constrained LCS**: Additional constraints on subsequence
- **Approximate LCS**: Allow some mismatches

### Related Problems
- **Longest Increasing Subsequence (LIS)**
- **Shortest Common Supersequence**
- **Longest Common Substring** (different from subsequence)
- **Edit Distance variants**

## Complexity Analysis

### Why O(m×n)?
- **Subproblems**: m×n possible combinations of prefixes
- **Each subproblem**: Solved once in DP
- **Transition**: Constant time per subproblem

### Space Complexity Reduction
- **Observation**: Only need current and previous row
- **Reduction**: From O(m×n) to O(min(m,n))
- **Trade-off**: Cannot reconstruct actual LCS easily

## Common Pitfalls

1. **Subsequence vs Substring**: Subsequence allows gaps
2. **0-based vs 1-based**: Careful with array indexing
3. **Memory Leaks**: Free allocated 2D arrays
4. **Integer Overflow**: For very long strings
5. **Empty Strings**: Handle edge cases properly

## Testing Strategies

### Test Cases
1. **Empty strings**: One or both empty
2. **Identical strings**: LCS should be the string itself
3. **No common characters**: LCS length should be 0
4. **Single character**: Simple cases
5. **Reversed strings**: Palindrome testing

### Performance Testing
1. **Small inputs**: Verify correctness with all algorithms
2. **Large inputs**: Test space-optimized version
3. **Random strings**: Various lengths and character sets
4. **Real-world data**: DNA sequences, text files

## Implementation Tips

1. **Use 0-based indexing** consistently
2. **Initialize DP table properly** (base cases)
3. **Handle string boundaries** carefully
4. **Free dynamically allocated memory**
5. **Consider string encoding** (ASCII vs Unicode)
6. **Validate input lengths** before processing
