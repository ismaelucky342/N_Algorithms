## N-Queens Problem

The N-Queens problem is a classic algorithmic challenge that involves placing N chess queens on an N×N chessboard so that no two queens threaten each other. This means that no two queens can share the same row, column, or diagonal.

## Implementation

In this project, the N-Queens problem is solved using a backtracking algorithm. The approach systematically explores all possible placements for the queens, row by row, and backtracks whenever a conflict is detected. The algorithm continues until all valid solutions are found.

Key steps in the implementation:
- Place a queen in a row and move to the next row.
- Check for conflicts with previously placed queens.
- If a conflict occurs, backtrack and try the next possible position.
- Repeat until all queens are placed or all possibilities are exhausted.

This method efficiently finds all possible solutions for the N-Queens problem.