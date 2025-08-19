#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto partition scheme
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1; // Index of smaller element
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Hoare partition scheme (alternative)
int hoare_partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j)
            return j;
        
        swap(&arr[i], &arr[j]);
    }
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void quick_sort_hoare(int arr[], int low, int high) {
    if (low < high) {
        int pi = hoare_partition(arr, low, high);
        
        quick_sort_hoare(arr, low, pi);
        quick_sort_hoare(arr, pi + 1, high);
    }
}

// Randomized Quick Sort to avoid worst case
int randomized_partition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void randomized_quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomized_partition(arr, low, high);
        
        randomized_quick_sort(arr, low, pi - 1);
        randomized_quick_sort(arr, pi + 1, high);
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

int main() {
    srand(time(NULL)); // Seed for random number generation
    
    int size, choice;
    
    printf("Enter array size: ");
    scanf("%d", &size);
    
    int *arr = malloc(size * sizeof(int));
    int *temp = malloc(size * sizeof(int));
    
    if (!arr || !temp) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("\nOriginal array: ");
    print_array(arr, size);
    
    printf("\nChoose Quick Sort variant:\n");
    printf("1. Standard Quick Sort (Lomuto partition)\n");
    printf("2. Quick Sort with Hoare partition\n");
    printf("3. Randomized Quick Sort\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);
    
    copy_array(arr, temp, size);
    
    clock_t start = clock();
    
    switch (choice) {
        case 1:
            printf("\nUsing Standard Quick Sort (Lomuto partition):\n");
            quick_sort(temp, 0, size - 1);
            break;
        case 2:
            printf("\nUsing Quick Sort with Hoare partition:\n");
            quick_sort_hoare(temp, 0, size - 1);
            break;
        case 3:
            printf("\nUsing Randomized Quick Sort:\n");
            randomized_quick_sort(temp, 0, size - 1);
            break;
        default:
            printf("\nInvalid choice! Using standard Quick Sort.\n");
            quick_sort(temp, 0, size - 1);
            break;
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Sorted array: ");
    print_array(temp, size);
    printf("Time taken: %f seconds\n", time_taken);
    
    free(arr);
    free(temp);
    return 0;
}
