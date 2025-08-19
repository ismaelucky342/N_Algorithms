#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes
int lcs_recursive(char *str1, char *str2, int m, int n);
int lcs_memoization(char *str1, char *str2, int m, int n, int **memo);
int lcs_dp(char *str1, char *str2, int m, int n);
int lcs_space_optimized(char *str1, char *str2, int m, int n);
void print_lcs(char *str1, char *str2, int m, int n);
void print_all_lcs(char *str1, char *str2, int m, int n);
int lcs_length_only(char *str1, char *str2);
void lcs_diff_algorithm(char *str1, char *str2);
int longest_palindromic_subsequence(char *str);
int edit_distance(char *str1, char *str2);
void print_dp_table(char *str1, char *str2, int m, int n);
int **allocate_2d_array(int rows, int cols);
void free_2d_array(int **arr, int rows);

// Recursive LCS (Exponential time - for small inputs only)
int lcs_recursive(char *str1, char *str2, int m, int n) {
    // Base case: if either string is empty
    if (m == 0 || n == 0)
        return 0;
    
    // If last characters match
    if (str1[m-1] == str2[n-1])
        return 1 + lcs_recursive(str1, str2, m-1, n-1);
    
    // If last characters don't match
    return max(lcs_recursive(str1, str2, m, n-1),
               lcs_recursive(str1, str2, m-1, n));
}

// Helper function for max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// LCS with Memoization (Top-down DP)
int lcs_memoization(char *str1, char *str2, int m, int n, int **memo) {
    // Base case
    if (m == 0 || n == 0)
        return 0;
    
    // If already computed
    if (memo[m][n] != -1)
        return memo[m][n];
    
    // If characters match
    if (str1[m-1] == str2[n-1])
        memo[m][n] = 1 + lcs_memoization(str1, str2, m-1, n-1, memo);
    else
        memo[m][n] = max(lcs_memoization(str1, str2, m, n-1, memo),
                        lcs_memoization(str1, str2, m-1, n, memo));
    
    return memo[m][n];
}

// LCS using Dynamic Programming (Bottom-up)
int lcs_dp(char *str1, char *str2, int m, int n) {
    int **dp = allocate_2d_array(m + 1, n + 1);
    
    // Build the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    int result = dp[m][n];
    free_2d_array(dp, m + 1);
    return result;
}

// Space-optimized LCS (O(min(m,n)) space)
int lcs_space_optimized(char *str1, char *str2, int m, int n) {
    // Make sure str1 is the shorter string
    if (m > n) {
        char *temp = str1;
        str1 = str2;
        str2 = temp;
        int temp_len = m;
        m = n;
        n = temp_len;
    }
    
    int *prev = calloc(m + 1, sizeof(int));
    int *curr = calloc(m + 1, sizeof(int));
    
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (str1[i-1] == str2[j-1])
                curr[i] = prev[i-1] + 1;
            else
                curr[i] = max(prev[i], curr[i-1]);
        }
        
        // Swap prev and curr
        int *temp = prev;
        prev = curr;
        curr = temp;
    }
    
    int result = prev[m];
    free(prev);
    free(curr);
    return result;
}

// Print the actual LCS
void print_lcs(char *str1, char *str2, int m, int n) {
    int **dp = allocate_2d_array(m + 1, n + 1);
    
    // Build the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Backtrack to find the LCS
    int lcs_length = dp[m][n];
    char *lcs = malloc((lcs_length + 1) * sizeof(char));
    lcs[lcs_length] = '\0';
    
    int i = m, j = n, index = lcs_length - 1;
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            lcs[index--] = str1[i-1];
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    printf("LCS: \"%s\" (Length: %d)\n", lcs, lcs_length);
    
    free(lcs);
    free_2d_array(dp, m + 1);
}

// Print DP table for visualization
void print_dp_table(char *str1, char *str2, int m, int n) {
    int **dp = allocate_2d_array(m + 1, n + 1);
    
    // Build the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Print the table
    printf("\nDP Table for LCS:\n");
    printf("    ε ");
    for (int j = 0; j < n; j++) {
        printf("%c ", str2[j]);
    }
    printf("\n");
    
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            printf("ε ");
        } else {
            printf("%c ", str1[i-1]);
        }
        
        for (int j = 0; j <= n; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    
    free_2d_array(dp, m + 1);
}

// LCS-based diff algorithm (simplified)
void lcs_diff_algorithm(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    int **dp = allocate_2d_array(m + 1, n + 1);
    
    // Build DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Generate diff
    printf("\nDiff (simplified):\n");
    int i = m, j = n;
    
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && str1[i-1] == str2[j-1]) {
            printf("  %c (common)\n", str1[i-1]);
            i--;
            j--;
        } else if (j > 0 && (i == 0 || dp[i][j-1] >= dp[i-1][j])) {
            printf("+ %c (added)\n", str2[j-1]);
            j--;
        } else if (i > 0) {
            printf("- %c (deleted)\n", str1[i-1]);
            i--;
        }
    }
    
    free_2d_array(dp, m + 1);
}

// Longest Palindromic Subsequence using LCS
int longest_palindromic_subsequence(char *str) {
    int n = strlen(str);
    char *reversed = malloc((n + 1) * sizeof(char));
    
    // Create reversed string
    for (int i = 0; i < n; i++) {
        reversed[i] = str[n - 1 - i];
    }
    reversed[n] = '\0';
    
    // LCS of string and its reverse
    int result = lcs_dp(str, reversed, n, n);
    
    free(reversed);
    return result;
}

// Edit Distance (Levenshtein Distance) using similar DP approach
int edit_distance(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    int **dp = allocate_2d_array(m + 1, n + 1);
    
    // Initialize base cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(dp[i-1][j],      // Deletion
                                  min(dp[i][j-1],    // Insertion
                                     dp[i-1][j-1])); // Substitution
        }
    }
    
    int result = dp[m][n];
    free_2d_array(dp, m + 1);
    return result;
}

// Helper function for min
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Utility functions for 2D array allocation
int **allocate_2d_array(int rows, int cols) {
    int **arr = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        arr[i] = calloc(cols, sizeof(int));
    }
    return arr;
}

void free_2d_array(int **arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

// Performance comparison function
void compare_lcs_algorithms(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    printf("\n=== Performance Comparison ===\n");
    printf("String 1: \"%s\" (length: %d)\n", str1, m);
    printf("String 2: \"%s\" (length: %d)\n", str2, n);
    
    clock_t start, end;
    
    // Recursive (only for small strings)
    if (m <= 10 && n <= 10) {
        start = clock();
        int result_recursive = lcs_recursive(str1, str2, m, n);
        end = clock();
        double time_recursive = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Recursive: Length = %d, Time = %f seconds\n", result_recursive, time_recursive);
    } else {
        printf("Recursive: Skipped (too slow for large inputs)\n");
    }
    
    // Memoization
    start = clock();
    int **memo = allocate_2d_array(m + 1, n + 1);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j] = -1;
        }
    }
    int result_memo = lcs_memoization(str1, str2, m, n, memo);
    end = clock();
    double time_memo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Memoization: Length = %d, Time = %f seconds\n", result_memo, time_memo);
    free_2d_array(memo, m + 1);
    
    // Dynamic Programming
    start = clock();
    int result_dp = lcs_dp(str1, str2, m, n);
    end = clock();
    double time_dp = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Dynamic Programming: Length = %d, Time = %f seconds\n", result_dp, time_dp);
    
    // Space Optimized
    start = clock();
    int result_optimized = lcs_space_optimized(str1, str2, m, n);
    end = clock();
    double time_optimized = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Space Optimized: Length = %d, Time = %f seconds\n", result_optimized, time_optimized);
}

int main() {
    char str1[1000], str2[1000];
    int choice;
    
    while (1) {
        printf("\n=== Longest Common Subsequence (LCS) ===\n");
        printf("1. Calculate LCS length (DP)\n");
        printf("2. Print actual LCS\n");
        printf("3. Show DP table\n");
        printf("4. Space-optimized LCS\n");
        printf("5. Compare all algorithms\n");
        printf("6. LCS-based diff\n");
        printf("7. Longest Palindromic Subsequence\n");
        printf("8. Edit Distance (Levenshtein)\n");
        printf("9. Predefined test cases\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                int length = lcs_dp(str1, str2, strlen(str1), strlen(str2));
                printf("LCS length: %d\n", length);
                break;
            }
            
            case 2: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                print_lcs(str1, str2, strlen(str1), strlen(str2));
                break;
            }
            
            case 3: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                print_dp_table(str1, str2, strlen(str1), strlen(str2));
                break;
            }
            
            case 4: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                int length = lcs_space_optimized(str1, str2, strlen(str1), strlen(str2));
                printf("LCS length (space optimized): %d\n", length);
                break;
            }
            
            case 5: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                compare_lcs_algorithms(str1, str2);
                break;
            }
            
            case 6: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                lcs_diff_algorithm(str1, str2);
                break;
            }
            
            case 7: {
                printf("Enter string: ");
                scanf("%s", str1);
                
                int length = longest_palindromic_subsequence(str1);
                printf("Longest palindromic subsequence length: %d\n", length);
                break;
            }
            
            case 8: {
                printf("Enter first string: ");
                scanf("%s", str1);
                printf("Enter second string: ");
                scanf("%s", str2);
                
                int distance = edit_distance(str1, str2);
                printf("Edit distance: %d\n", distance);
                break;
            }
            
            case 9: {
                printf("\n=== Predefined Test Cases ===\n");
                
                // Test case 1
                strcpy(str1, "ABCDGH");
                strcpy(str2, "AEDFHR");
                printf("Test 1: \"%s\" and \"%s\"\n", str1, str2);
                print_lcs(str1, str2, strlen(str1), strlen(str2));
                
                // Test case 2
                strcpy(str1, "AGGTAB");
                strcpy(str2, "GXTXAYB");
                printf("\nTest 2: \"%s\" and \"%s\"\n", str1, str2);
                print_lcs(str1, str2, strlen(str1), strlen(str2));
                
                // Test case 3
                strcpy(str1, "programming");
                strcpy(str2, "algorithm");
                printf("\nTest 3: \"%s\" and \"%s\"\n", str1, str2);
                print_lcs(str1, str2, strlen(str1), strlen(str2));
                
                // Test case 4 - Palindrome
                strcpy(str1, "racecar");
                printf("\nTest 4: Longest palindromic subsequence of \"%s\"\n", str1);
                printf("Length: %d\n", longest_palindromic_subsequence(str1));
                
                break;
            }
            
            case 10: {
                printf("Goodbye!\n");
                return 0;
            }
            
            default: {
                printf("Invalid choice! Please try again.\n");
                break;
            }
        }
    }
    
    return 0;
}
