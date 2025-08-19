#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    if (!L || !R) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Iterative Merge Sort
void merge_sort_iterative(int arr[], int n) {
    int curr_size; // Current size of subarrays to be merged
    int left_start; // Starting index of left sub-array
    
    // Merge subarrays in bottom-up manner
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // Pick starting point of left sub array
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            // Calculate mid point to break the sub array in two halves
            int mid = (left_start + curr_size - 1 < n - 1) ? 
                      left_start + curr_size - 1 : n - 1;
            
            // Calculate end point of right sub array
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? 
                           left_start + 2 * curr_size - 1 : n - 1;
            
            // Merge subarrays if mid is smaller than right_end
            if (mid < right_end)
                merge(arr, left_start, mid, right_end);
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copy_array(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Function to generate random array for testing
void generate_random_array(int arr[], int size, int max_val) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % max_val;
    }
}

int main() {
    srand(time(NULL));
    
    int size, choice, input_choice;
    
    printf("Enter array size: ");
    scanf("%d", &size);
    
    int *arr = malloc(size * sizeof(int));
    int *temp1 = malloc(size * sizeof(int));
    int *temp2 = malloc(size * sizeof(int));
    
    if (!arr || !temp1 || !temp2) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("\nChoose input method:\n");
    printf("1. Manual input\n");
    printf("2. Random generation\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &input_choice);
    
    if (input_choice == 1) {
        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    } else {
        generate_random_array(arr, size, 1000);
        printf("Generated random array:\n");
    }
    
    printf("\nOriginal array: ");
    print_array(arr, size);
    
    printf("\nChoose Merge Sort variant:\n");
    printf("1. Recursive Merge Sort\n");
    printf("2. Iterative Merge Sort\n");
    printf("3. Compare both methods\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);
    
    clock_t start, end;
    double time1, time2;
    
    switch (choice) {
        case 1:
            copy_array(arr, temp1, size);
            start = clock();
            merge_sort(temp1, 0, size - 1);
            end = clock();
            time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("\nUsing Recursive Merge Sort:\n");
            printf("Sorted array: ");
            print_array(temp1, size);
            printf("Time taken: %f seconds\n", time1);
            break;
            
        case 2:
            copy_array(arr, temp1, size);
            start = clock();
            merge_sort_iterative(temp1, size);
            end = clock();
            time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("\nUsing Iterative Merge Sort:\n");
            printf("Sorted array: ");
            print_array(temp1, size);
            printf("Time taken: %f seconds\n", time1);
            break;
            
        case 3:
            // Recursive
            copy_array(arr, temp1, size);
            start = clock();
            merge_sort(temp1, 0, size - 1);
            end = clock();
            time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            // Iterative
            copy_array(arr, temp2, size);
            start = clock();
            merge_sort_iterative(temp2, size);
            end = clock();
            time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("\nComparison Results:\n");
            printf("Recursive Merge Sort time: %f seconds\n", time1);
            printf("Iterative Merge Sort time: %f seconds\n", time2);
            printf("Sorted array: ");
            print_array(temp1, size);
            break;
            
        default:
            printf("\nInvalid choice! Using recursive merge sort.\n");
            copy_array(arr, temp1, size);
            merge_sort(temp1, 0, size - 1);
            printf("Sorted array: ");
            print_array(temp1, size);
            break;
    }
    
    free(arr);
    free(temp1);
    free(temp2);
    return 0;
}
