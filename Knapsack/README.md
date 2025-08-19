# Knapsack Problem Algorithms

## Description
The Knapsack Problem is a classic optimization problem where you have a knapsack with limited capacity and items with different weights and values. The goal is to maximize the total value while staying within the weight limit.

## Problem Variants

### 1. 0/1 Knapsack (Binary Knapsack)
- Each item can be taken **at most once**
- Decision: include or exclude each item
- **Time Complexity**: O(n × W) where n = items, W = capacity
- **Space Complexity**: O(n × W) or O(W) with optimization

### 2. Unbounded Knapsack
- Each item can be taken **unlimited times**
- Similar to coin change problem
- **Time Complexity**: O(n × W)
- **Space Complexity**: O(W)

### 3. Fractional Knapsack
- Items can be **partially taken**
- Uses greedy approach (value-to-weight ratio)
- **Time Complexity**: O(n log n) for sorting
- **Space Complexity**: O(n)

## Implementations Included

### Dynamic Programming Solutions
- **Full DP Table**: Shows complete state transition
- **Space Optimized**: Uses 1D array instead of 2D
- **With Item Tracking**: Shows which items were selected
- **DP Table Visualization**: Displays the computation process

### Greedy Solution
- **Fractional Knapsack**: Optimal for fractional variant
- **Sorted by Ratio**: Items sorted by value/weight ratio

## How to Compile and Run

```bash
gcc -o knapsack knapsack.c
./knapsack
```

## Example Usage

```
Enter number of items: 4
Enter knapsack capacity: 10
Enter items (name weight value):
Gold 2 3
Silver 3 4
Bronze 4 5
Platinum 5 6

Items entered:
Item            Weight  Value   Value/Weight
--------------------------------------------
Gold            2       3       1.50
Silver          3       4       1.33
Bronze          4       5       1.25
Platinum        5       6       1.20

--- Knapsack Problem Solutions ---
1. 0/1 Knapsack (DP - Full table)
2. 0/1 Knapsack (DP - Optimized space)
3. 0/1 Knapsack with selected items
4. Unbounded Knapsack
5. Fractional Knapsack (Greedy)
6. Show DP table
7. Exit
Enter your choice: 3

Selected items:
Item            Weight  Value
--------------------------------
Bronze          4       5
Silver          3       4
Gold            2       3
--------------------------------
Total value: 12
Total weight: 9 / 10
```

## Algorithm Analysis

### 0/1 Knapsack DP Recurrence
```
dp[i][w] = max(
    dp[i-1][w],                    // Don't take item i
    dp[i-1][w-weight[i]] + value[i] // Take item i (if fits)
)
```

### Base Cases
- `dp[0][w] = 0` for all w (no items)
- `dp[i][0] = 0` for all i (no capacity)

### Space Optimization
- Use 1D array instead of 2D
- Process from right to left to avoid conflicts
- Reduces space from O(n×W) to O(W)

## Problem Characteristics

### 0/1 Knapsack Properties
- **Optimal Substructure**: Optimal solution contains optimal solutions to subproblems
- **Overlapping Subproblems**: Same subproblems solved multiple times
- **No Greedy Solution**: Greedy by value/weight ratio doesn't work

### When to Use Each Variant

#### Use 0/1 Knapsack when:
- Items are discrete and indivisible
- Each item has limited quantity (usually 1)
- Need exact optimal solution

#### Use Unbounded Knapsack when:
- Items can be used multiple times
- Resource allocation problems
- Coin change variations

#### Use Fractional Knapsack when:
- Items can be divided (liquids, powders)
- Approximation is acceptable
- Need fast solution

## Real-World Applications

### 0/1 Knapsack
- **Resource Allocation**: Limited budget, discrete projects
- **Cargo Loading**: Ships, trucks with weight limits
- **Investment Portfolio**: Limited capital, discrete investments

### Unbounded Knapsack
- **Currency Exchange**: Unlimited coins of each denomination
- **Production Planning**: Unlimited raw materials
- **Storage Optimization**: Repeated patterns

### Fractional Knapsack
- **Chemical Mixing**: Divisible materials
- **Network Bandwidth**: Divisible data streams
- **Financial Trading**: Partial shares

## Complexity Comparison

| Variant | Time | Space | Approach | Optimal |
|---------|------|-------|----------|---------|
| 0/1 DP | O(nW) | O(nW) or O(W) | Dynamic Programming | Yes |
| Unbounded | O(nW) | O(W) | Dynamic Programming | Yes |
| Fractional | O(n log n) | O(n) | Greedy | Yes |

## Tips for Problem Solving

1. **Identify Variant**: Can items be repeated? Can they be fractional?
2. **Check Constraints**: Small W suggests DP, large W might need approximation
3. **Space Optimization**: Use 1D DP when possible
4. **Item Reconstruction**: Track choices if you need the actual items
5. **Edge Cases**: Handle zero capacity, no items, negative values

## Extensions and Variations

- **Multiple Knapsacks**: Several knapsacks with different capacities
- **2D Knapsack**: Weight and volume constraints
- **Bounded Knapsack**: Limited quantity for each item type
- **Online Knapsack**: Items arrive dynamically
