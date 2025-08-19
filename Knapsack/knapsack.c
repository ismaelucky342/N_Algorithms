#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0/1 Knapsack using Dynamic Programming
int knapsack_01_dp(int capacity, int weights[], int values[], int n) {
    // Create a 2D DP table
    int **dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = calloc(capacity + 1, sizeof(int));
    }
    
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                // Max of including or excluding current item
                int include = values[i-1] + dp[i-1][w - weights[i-1]];
                int exclude = dp[i-1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                // Can't include current item
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    int result = dp[n][capacity];
    
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// 0/1 Knapsack with space optimization
int knapsack_01_optimized(int capacity, int weights[], int values[], int n) {
    int *dp = calloc(capacity + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        // Traverse from right to left to avoid using updated values
        for (int w = capacity; w >= weights[i]; w--) {
            int include = values[i] + dp[w - weights[i]];
            if (include > dp[w]) {
                dp[w] = include;
            }
        }
    }
    
    int result = dp[capacity];
    free(dp);
    return result;
}

// 0/1 Knapsack with item tracking
void knapsack_01_with_items(int capacity, int weights[], int values[], int n, 
                           char items[][50]) {
    // Create a 2D DP table
    int **dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = calloc(capacity + 1, sizeof(int));
    }
    
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                int include = values[i-1] + dp[i-1][w - weights[i-1]];
                int exclude = dp[i-1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    // Backtrack to find which items were selected
    int w = capacity;
    int total_weight = 0;
    printf("\nSelected items:\n");
    printf("Item\t\tWeight\tValue\n");
    printf("--------------------------------\n");
    
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("%-15s\t%d\t%d\n", items[i-1], weights[i-1], values[i-1]);
            w -= weights[i-1];
            total_weight += weights[i-1];
        }
    }
    
    printf("--------------------------------\n");
    printf("Total value: %d\n", dp[n][capacity]);
    printf("Total weight: %d / %d\n", total_weight, capacity);
    
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

// Unbounded Knapsack (unlimited items)
int knapsack_unbounded(int capacity, int weights[], int values[], int n) {
    int *dp = calloc(capacity + 1, sizeof(int));
    
    for (int w = 1; w <= capacity; w++) {
        for (int i = 0; i < n; i++) {
            if (weights[i] <= w) {
                int include = values[i] + dp[w - weights[i]];
                if (include > dp[w]) {
                    dp[w] = include;
                }
            }
        }
    }
    
    int result = dp[capacity];
    free(dp);
    return result;
}

// Fractional Knapsack (Greedy approach)
typedef struct {
    int weight;
    int value;
    double ratio;
    char name[50];
    int index;
} Item;

int compare_items(const void *a, const void *b) {
    Item *itemA = (Item*)a;
    Item *itemB = (Item*)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

double knapsack_fractional(int capacity, int weights[], int values[], int n, 
                          char items[][50]) {
    Item *item_array = malloc(n * sizeof(Item));
    
    // Create items with value-to-weight ratio
    for (int i = 0; i < n; i++) {
        item_array[i].weight = weights[i];
        item_array[i].value = values[i];
        item_array[i].ratio = (double)values[i] / weights[i];
        strcpy(item_array[i].name, items[i]);
        item_array[i].index = i;
    }
    
    // Sort by value-to-weight ratio (descending)
    qsort(item_array, n, sizeof(Item), compare_items);
    
    double total_value = 0.0;
    int remaining_capacity = capacity;
    
    printf("\nFractional Knapsack solution:\n");
    printf("Item\t\tWeight\tValue\tRatio\tTaken\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        if (remaining_capacity >= item_array[i].weight) {
            // Take the whole item
            total_value += item_array[i].value;
            remaining_capacity -= item_array[i].weight;
            printf("%-15s\t%d\t%d\t%.2f\t100%%\n", 
                   item_array[i].name, item_array[i].weight, 
                   item_array[i].value, item_array[i].ratio);
        } else if (remaining_capacity > 0) {
            // Take fraction of the item
            double fraction = (double)remaining_capacity / item_array[i].weight;
            total_value += item_array[i].value * fraction;
            printf("%-15s\t%d\t%d\t%.2f\t%.1f%%\n", 
                   item_array[i].name, item_array[i].weight, 
                   item_array[i].value, item_array[i].ratio, fraction * 100);
            remaining_capacity = 0;
            break;
        }
    }
    
    printf("------------------------------------------------\n");
    printf("Total value: %.2f\n", total_value);
    
    free(item_array);
    return total_value;
}

void print_knapsack_table(int capacity, int weights[], int values[], int n) {
    printf("\nDP Table for 0/1 Knapsack:\n");
    printf("Capacity: ");
    for (int w = 0; w <= capacity; w++) {
        printf("%4d", w);
    }
    printf("\n");
    
    int **dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = calloc(capacity + 1, sizeof(int));
    }
    
    // Fill the DP table and print
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("Item 0:  ");
        } else {
            printf("Item %d:  ", i);
        }
        
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i-1] <= w) {
                int include = values[i-1] + dp[i-1][w - weights[i-1]];
                int exclude = dp[i-1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i-1][w];
            }
            printf("%4d", dp[i][w]);
        }
        printf("\n");
    }
    
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

int main() {
    int n, capacity, choice;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid number of items!\n");
        return 1;
    }
    
    int *weights = malloc(n * sizeof(int));
    int *values = malloc(n * sizeof(int));
    char (*items)[50] = malloc(n * sizeof(char[50]));
    
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);
    
    printf("Enter items (name weight value):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", items[i], &weights[i], &values[i]);
        if (weights[i] <= 0 || values[i] <= 0) {
            printf("Invalid weight or value! Please enter positive values.\n");
            i--;
            continue;
        }
    }
    
    // Display items
    printf("\nItems entered:\n");
    printf("Item\t\tWeight\tValue\tValue/Weight\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s\t%d\t%d\t%.2f\n", items[i], weights[i], values[i], 
               (double)values[i] / weights[i]);
    }
    
    do {
        printf("\n--- Knapsack Problem Solutions ---\n");
        printf("1. 0/1 Knapsack (DP - Full table)\n");
        printf("2. 0/1 Knapsack (DP - Optimized space)\n");
        printf("3. 0/1 Knapsack with selected items\n");
        printf("4. Unbounded Knapsack\n");
        printf("5. Fractional Knapsack (Greedy)\n");
        printf("6. Show DP table\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int max_value = knapsack_01_dp(capacity, weights, values, n);
                printf("Maximum value (0/1 Knapsack): %d\n", max_value);
                break;
            }
            case 2: {
                int max_value = knapsack_01_optimized(capacity, weights, values, n);
                printf("Maximum value (Optimized 0/1 Knapsack): %d\n", max_value);
                break;
            }
            case 3: {
                knapsack_01_with_items(capacity, weights, values, n, items);
                break;
            }
            case 4: {
                int max_value = knapsack_unbounded(capacity, weights, values, n);
                printf("Maximum value (Unbounded Knapsack): %d\n", max_value);
                break;
            }
            case 5: {
                double max_value = knapsack_fractional(capacity, weights, values, n, items);
                printf("Maximum value (Fractional Knapsack): %.2f\n", max_value);
                break;
            }
            case 6: {
                print_knapsack_table(capacity, weights, values, n);
                break;
            }
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 7);
    
    free(weights);
    free(values);
    free(items);
    return 0;
}
