#include <stdio.h>
#include <stdlib.h>

// Iterative Binary Search
int binary_search_iterative(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return mid;
        
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Element not found
}

// Recursive Binary Search
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return mid;
        
        if (arr[mid] > target)
            return binary_search_recursive(arr, left, mid - 1, target);
        
        return binary_search_recursive(arr, mid + 1, right, target);
    }
    return -1; // Element not found
}

void print_array(int arr[], int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size, target, choice;
    
    printf("Enter array size: ");
    scanf("%d", &size);
    
    int *arr = malloc(size * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d sorted elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    print_array(arr, size);
    
    printf("Enter target element to search: ");
    scanf("%d", &target);
    
    printf("Choose search method:\n");
    printf("1. Iterative Binary Search\n");
    printf("2. Recursive Binary Search\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);
    
    int result = -1;
    
    switch (choice) {
        case 1:
            result = binary_search_iterative(arr, 0, size - 1, target);
            printf("Using Iterative Binary Search:\n");
            break;
        case 2:
            result = binary_search_recursive(arr, 0, size - 1, target);
            printf("Using Recursive Binary Search:\n");
            break;
        default:
            printf("Invalid choice! Using iterative search by default.\n");
            result = binary_search_iterative(arr, 0, size - 1, target);
            break;
    }
    
    if (result != -1)
        printf("Element %d found at index %d\n", target, result);
    else
        printf("Element %d not found in the array\n", target);
    
    free(arr);
    return 0;
}
