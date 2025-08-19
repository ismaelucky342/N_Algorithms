#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Binary Heap structure
typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

// Function prototypes
Heap* create_heap(int capacity);
void free_heap(Heap* heap);
void swap(int *a, int *b);
void max_heapify(int arr[], int n, int i);
void min_heapify(int arr[], int n, int i);
void build_max_heap(int arr[], int n);
void build_min_heap(int arr[], int n);
void heap_sort_ascending(int arr[], int n);
void heap_sort_descending(int arr[], int n);
void insert_heap(Heap* heap, int key);
int extract_max(Heap* heap);
int extract_min(Heap* heap);
int get_max(Heap* heap);
int get_min(Heap* heap);
void increase_key(Heap* heap, int i, int new_key);
void decrease_key(Heap* heap, int i, int new_key);
void delete_key(Heap* heap, int i);
void print_array(int arr[], int n);
void print_heap(Heap* heap);
void copy_array(int source[], int dest[], int n);
int is_max_heap(int arr[], int n);
int is_min_heap(int arr[], int n);

// Create a new heap
Heap* create_heap(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    if (!heap) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    heap->data = malloc(capacity * sizeof(int));
    if (!heap->data) {
        printf("Memory allocation failed!\n");
        free(heap);
        exit(1);
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Free heap memory
void free_heap(Heap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

// Swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify a subtree rooted with node i (Max Heap)
void max_heapify(int arr[], int n, int i) {
    int largest = i;    // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        
        // Recursively heapify the affected sub-tree
        max_heapify(arr, n, largest);
    }
}

// Heapify a subtree rooted with node i (Min Heap)
void min_heapify(int arr[], int n, int i) {
    int smallest = i;    // Initialize smallest as root
    int left = 2 * i + 1;    // Left child
    int right = 2 * i + 2;   // Right child
    
    // If left child is smaller than root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    
    // If right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
    
    // If smallest is not root
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        
        // Recursively heapify the affected sub-tree
        min_heapify(arr, n, smallest);
    }
}

// Build a max heap from array
void build_max_heap(int arr[], int n) {
    // Start from rightmost internal node and heapify all internal nodes
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(arr, n, i);
    }
}

// Build a min heap from array
void build_min_heap(int arr[], int n) {
    // Start from rightmost internal node and heapify all internal nodes
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify(arr, n, i);
    }
}

// Heap sort (ascending order)
void heap_sort_ascending(int arr[], int n) {
    // Build max heap
    build_max_heap(arr, n);
    
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);
        
        // Call max heapify on the reduced heap
        max_heapify(arr, i, 0);
    }
}

// Heap sort (descending order)
void heap_sort_descending(int arr[], int n) {
    // Build min heap
    build_min_heap(arr, n);
    
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);
        
        // Call min heapify on the reduced heap
        min_heapify(arr, i, 0);
    }
}

// Insert a new key into max heap
void insert_heap(Heap* heap, int key) {
    if (heap->size >= heap->capacity) {
        printf("Heap overflow! Cannot insert %d\n", key);
        return;
    }
    
    // First insert the new key at the end
    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = key;
    
    // Fix the max heap property if it is violated
    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    
    printf("Inserted %d into heap.\n", key);
}

// Extract maximum element from max heap
int extract_max(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow!\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    // Store the maximum value, and remove it from heap
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    max_heapify(heap->data, heap->size, 0);
    
    return root;
}

// Extract minimum element from min heap
int extract_min(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow!\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    // Store the minimum value, and remove it from heap
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    min_heapify(heap->data, heap->size, 0);
    
    return root;
}

// Get maximum element (root of max heap)
int get_max(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->data[0];
}

// Get minimum element (root of min heap)
int get_min(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->data[0];
}

// Increase value of key at index i to new_key (for max heap)
void increase_key(Heap* heap, int i, int new_key) {
    if (i >= heap->size) {
        printf("Invalid index!\n");
        return;
    }
    if (new_key < heap->data[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }
    
    heap->data[i] = new_key;
    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("Key increased successfully.\n");
}

// Decrease value of key at index i to new_key (for min heap)
void decrease_key(Heap* heap, int i, int new_key) {
    if (i >= heap->size) {
        printf("Invalid index!\n");
        return;
    }
    if (new_key > heap->data[i]) {
        printf("New key is larger than current key!\n");
        return;
    }
    
    heap->data[i] = new_key;
    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("Key decreased successfully.\n");
}

// Delete key at index i
void delete_key(Heap* heap, int i) {
    if (i >= heap->size) {
        printf("Invalid index!\n");
        return;
    }
    
    // Replace the key with last key
    heap->data[i] = heap->data[heap->size - 1];
    heap->size--;
    
    // Heapify from the changed node
    max_heapify(heap->data, heap->size, i);
    
    // Also check if we need to move up
    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    
    printf("Key deleted successfully.\n");
}

// Print array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Print heap with tree-like structure
void print_heap(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }
    
    printf("Heap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
    
    printf("Heap tree structure:\n");
    int level = 0;
    int level_size = 1;
    int printed = 0;
    
    while (printed < heap->size) {
        for (int i = 0; i < level; i++) printf("  ");
        
        for (int i = 0; i < level_size && printed < heap->size; i++) {
            printf("%d ", heap->data[printed]);
            printed++;
        }
        printf("\n");
        level++;
        level_size *= 2;
    }
}

// Copy array
void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

// Check if array represents a max heap
int is_max_heap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        // Left child
        if (2 * i + 1 < n && arr[i] < arr[2 * i + 1])
            return 0;
        
        // Right child
        if (2 * i + 2 < n && arr[i] < arr[2 * i + 2])
            return 0;
    }
    return 1;
}

// Check if array represents a min heap
int is_min_heap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        // Left child
        if (2 * i + 1 < n && arr[i] > arr[2 * i + 1])
            return 0;
        
        // Right child
        if (2 * i + 2 < n && arr[i] > arr[2 * i + 2])
            return 0;
    }
    return 1;
}

// Generate random array for testing
void generate_random_array(int arr[], int n, int max_val) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_val + 1;
    }
}

int main() {
    srand(time(NULL));
    
    int choice;
    Heap* max_heap = NULL;
    Heap* min_heap = NULL;
    
    while (1) {
        printf("\n=== Heap Sort and Binary Heap Operations ===\n");
        printf("HEAP SORT:\n");
        printf("1. Heap Sort (Ascending)\n");
        printf("2. Heap Sort (Descending)\n");
        printf("3. Compare with array sorting\n");
        
        printf("\nMAX HEAP OPERATIONS:\n");
        printf("4. Create Max Heap\n");
        printf("5. Insert into Max Heap\n");
        printf("6. Extract Maximum\n");
        printf("7. Get Maximum\n");
        printf("8. Increase Key\n");
        printf("9. Delete Key\n");
        printf("10. Display Max Heap\n");
        
        printf("\nMIN HEAP OPERATIONS:\n");
        printf("11. Create Min Heap\n");
        printf("12. Insert into Min Heap\n");
        printf("13. Extract Minimum\n");
        printf("14. Get Minimum\n");
        printf("15. Decrease Key\n");
        printf("16. Display Min Heap\n");
        
        printf("\nUTILITIES:\n");
        printf("17. Check if array is Max Heap\n");
        printf("18. Check if array is Min Heap\n");
        printf("19. Build heap from array\n");
        printf("20. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                
                int *arr = malloc(n * sizeof(int));
                printf("Choose input method:\n1. Manual\n2. Random\nChoice: ");
                int input_choice;
                scanf("%d", &input_choice);
                
                if (input_choice == 1) {
                    printf("Enter %d elements: ", n);
                    for (int i = 0; i < n; i++) {
                        scanf("%d", &arr[i]);
                    }
                } else {
                    generate_random_array(arr, n, 100);
                }
                
                printf("Original array: ");
                print_array(arr, n);
                
                clock_t start = clock();
                heap_sort_ascending(arr, n);
                clock_t end = clock();
                
                printf("Sorted array (ascending): ");
                print_array(arr, n);
                printf("Time taken: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
                
                free(arr);
                break;
            }
            
            case 2: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                
                int *arr = malloc(n * sizeof(int));
                printf("Choose input method:\n1. Manual\n2. Random\nChoice: ");
                int input_choice;
                scanf("%d", &input_choice);
                
                if (input_choice == 1) {
                    printf("Enter %d elements: ", n);
                    for (int i = 0; i < n; i++) {
                        scanf("%d", &arr[i]);
                    }
                } else {
                    generate_random_array(arr, n, 100);
                }
                
                printf("Original array: ");
                print_array(arr, n);
                
                heap_sort_descending(arr, n);
                
                printf("Sorted array (descending): ");
                print_array(arr, n);
                
                free(arr);
                break;
            }
            
            case 3: {
                printf("This option would compare heap sort with other sorting algorithms.\n");
                printf("You can implement quick sort and merge sort comparison here.\n");
                break;
            }
            
            case 4: {
                if (max_heap) free_heap(max_heap);
                int capacity;
                printf("Enter max heap capacity: ");
                scanf("%d", &capacity);
                max_heap = create_heap(capacity);
                printf("Max heap created with capacity %d.\n", capacity);
                break;
            }
            
            case 5: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                int key;
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert_heap(max_heap, key);
                break;
            }
            
            case 6: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                int max = extract_max(max_heap);
                if (max != -1) {
                    printf("Extracted maximum: %d\n", max);
                }
                break;
            }
            
            case 7: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                int max = get_max(max_heap);
                if (max != -1) {
                    printf("Maximum element: %d\n", max);
                }
                break;
            }
            
            case 8: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                int index, new_key;
                printf("Enter index and new key: ");
                scanf("%d %d", &index, &new_key);
                increase_key(max_heap, index, new_key);
                break;
            }
            
            case 9: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                int index;
                printf("Enter index to delete: ");
                scanf("%d", &index);
                delete_key(max_heap, index);
                break;
            }
            
            case 10: {
                if (!max_heap) {
                    printf("Create max heap first!\n");
                    break;
                }
                printf("Max Heap:\n");
                print_heap(max_heap);
                break;
            }
            
            case 11: {
                if (min_heap) free_heap(min_heap);
                int capacity;
                printf("Enter min heap capacity: ");
                scanf("%d", &capacity);
                min_heap = create_heap(capacity);
                printf("Min heap created with capacity %d.\n", capacity);
                break;
            }
            
            case 12: {
                if (!min_heap) {
                    printf("Create min heap first!\n");
                    break;
                }
                int key;
                printf("Enter key to insert: ");
                scanf("%d", &key);
                // For min heap, we need to modify insertion logic
                if (min_heap->size >= min_heap->capacity) {
                    printf("Heap overflow!\n");
                    break;
                }
                min_heap->size++;
                int i = min_heap->size - 1;
                min_heap->data[i] = key;
                
                // Fix min heap property
                while (i != 0 && min_heap->data[(i - 1) / 2] > min_heap->data[i]) {
                    swap(&min_heap->data[i], &min_heap->data[(i - 1) / 2]);
                    i = (i - 1) / 2;
                }
                printf("Inserted %d into min heap.\n", key);
                break;
            }
            
            case 13: {
                if (!min_heap) {
                    printf("Create min heap first!\n");
                    break;
                }
                int min = extract_min(min_heap);
                if (min != -1) {
                    printf("Extracted minimum: %d\n", min);
                }
                break;
            }
            
            case 14: {
                if (!min_heap) {
                    printf("Create min heap first!\n");
                    break;
                }
                int min = get_min(min_heap);
                if (min != -1) {
                    printf("Minimum element: %d\n", min);
                }
                break;
            }
            
            case 15: {
                if (!min_heap) {
                    printf("Create min heap first!\n");
                    break;
                }
                int index, new_key;
                printf("Enter index and new key: ");
                scanf("%d %d", &index, &new_key);
                decrease_key(min_heap, index, new_key);
                break;
            }
            
            case 16: {
                if (!min_heap) {
                    printf("Create min heap first!\n");
                    break;
                }
                printf("Min Heap:\n");
                print_heap(min_heap);
                break;
            }
            
            case 17: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                int *arr = malloc(n * sizeof(int));
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                
                if (is_max_heap(arr, n)) {
                    printf("Array represents a valid max heap.\n");
                } else {
                    printf("Array does NOT represent a valid max heap.\n");
                }
                free(arr);
                break;
            }
            
            case 18: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                int *arr = malloc(n * sizeof(int));
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                
                if (is_min_heap(arr, n)) {
                    printf("Array represents a valid min heap.\n");
                } else {
                    printf("Array does NOT represent a valid min heap.\n");
                }
                free(arr);
                break;
            }
            
            case 19: {
                int n, heap_type;
                printf("Enter array size: ");
                scanf("%d", &n);
                int *arr = malloc(n * sizeof(int));
                printf("Enter %d elements: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                
                printf("Original array: ");
                print_array(arr, n);
                
                printf("Build: 1. Max Heap  2. Min Heap\nChoice: ");
                scanf("%d", &heap_type);
                
                if (heap_type == 1) {
                    build_max_heap(arr, n);
                    printf("Max heap built: ");
                } else {
                    build_min_heap(arr, n);
                    printf("Min heap built: ");
                }
                print_array(arr, n);
                free(arr);
                break;
            }
            
            case 20: {
                if (max_heap) free_heap(max_heap);
                if (min_heap) free_heap(min_heap);
                printf("Goodbye!\n");
                return 0;
            }
            
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
    
    return 0;
}
