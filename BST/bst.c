#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// BST Node structure
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function prototypes
BSTNode* create_node(int data);
BSTNode* insert(BSTNode* root, int data);
BSTNode* search(BSTNode* root, int data);
BSTNode* delete_node(BSTNode* root, int data);
BSTNode* find_min(BSTNode* root);
BSTNode* find_max(BSTNode* root);
void inorder_traversal(BSTNode* root);
void preorder_traversal(BSTNode* root);
void postorder_traversal(BSTNode* root);
void level_order_traversal(BSTNode* root);
int height(BSTNode* root);
int count_nodes(BSTNode* root);
bool is_valid_bst(BSTNode* root, int min_val, int max_val);
BSTNode* lowest_common_ancestor(BSTNode* root, int n1, int n2);
void print_range(BSTNode* root, int k1, int k2);
BSTNode* kth_smallest(BSTNode* root, int k, int* count);
BSTNode* kth_largest(BSTNode* root, int k, int* count);
void free_tree(BSTNode* root);
void print_tree_structure(BSTNode* root, int space);
bool path_to_node(BSTNode* root, int target, int path[], int* path_length);
int distance_between_nodes(BSTNode* root, int n1, int n2);

// Queue for level order traversal
typedef struct QueueNode {
    BSTNode* tree_node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* create_queue();
void enqueue(Queue* q, BSTNode* node);
BSTNode* dequeue(Queue* q);
bool is_queue_empty(Queue* q);
void free_queue(Queue* q);

// Create a new BST node
BSTNode* create_node(int data) {
    BSTNode* new_node = malloc(sizeof(BSTNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert a node into BST
BSTNode* insert(BSTNode* root, int data) {
    // Base case: empty tree
    if (root == NULL) {
        return create_node(data);
    }
    
    // Recursive case
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        // Duplicate values not allowed
        printf("Value %d already exists in the tree!\n", data);
    }
    
    return root;
}

// Search for a value in BST
BSTNode* search(BSTNode* root, int data) {
    // Base case: empty tree or found
    if (root == NULL || root->data == data) {
        return root;
    }
    
    // Search left or right subtree
    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Find minimum value node
BSTNode* find_min(BSTNode* root) {
    if (root == NULL) return NULL;
    
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Find maximum value node
BSTNode* find_max(BSTNode* root) {
    if (root == NULL) return NULL;
    
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Delete a node from BST
BSTNode* delete_node(BSTNode* root, int data) {
    if (root == NULL) {
        printf("Value %d not found in the tree!\n", data);
        return root;
    }
    
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // Node to be deleted found
        
        // Case 1: No children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Case 2: One child
        else if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: Two children
        else {
            BSTNode* temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }
    return root;
}

// Inorder traversal (Left-Root-Right) - gives sorted order
void inorder_traversal(BSTNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// Preorder traversal (Root-Left-Right)
void preorder_traversal(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

// Postorder traversal (Left-Right-Root)
void postorder_traversal(BSTNode* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

// Level order traversal (Breadth-First)
void level_order_traversal(BSTNode* root) {
    if (root == NULL) return;
    
    Queue* q = create_queue();
    enqueue(q, root);
    
    while (!is_queue_empty(q)) {
        BSTNode* current = dequeue(q);
        printf("%d ", current->data);
        
        if (current->left) enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }
    
    free_queue(q);
}

// Calculate height of the tree
int height(BSTNode* root) {
    if (root == NULL) return -1;
    
    int left_height = height(root->left);
    int right_height = height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Count total number of nodes
int count_nodes(BSTNode* root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Validate if tree is a valid BST
bool is_valid_bst(BSTNode* root, int min_val, int max_val) {
    if (root == NULL) return true;
    
    if (root->data <= min_val || root->data >= max_val) {
        return false;
    }
    
    return is_valid_bst(root->left, min_val, root->data) &&
           is_valid_bst(root->right, root->data, max_val);
}

// Find Lowest Common Ancestor
BSTNode* lowest_common_ancestor(BSTNode* root, int n1, int n2) {
    if (root == NULL) return NULL;
    
    // If both n1 and n2 are smaller than root, LCA lies in left subtree
    if (n1 < root->data && n2 < root->data) {
        return lowest_common_ancestor(root->left, n1, n2);
    }
    
    // If both n1 and n2 are greater than root, LCA lies in right subtree
    if (n1 > root->data && n2 > root->data) {
        return lowest_common_ancestor(root->right, n1, n2);
    }
    
    // If one is smaller and other is greater, then root is LCA
    return root;
}

// Print all nodes in given range
void print_range(BSTNode* root, int k1, int k2) {
    if (root == NULL) return;
    
    // If root's data is greater than k1, recur for left subtree
    if (k1 < root->data) {
        print_range(root->left, k1, k2);
    }
    
    // If root's data is in range, print it
    if (k1 <= root->data && root->data <= k2) {
        printf("%d ", root->data);
    }
    
    // If root's data is smaller than k2, recur for right subtree
    if (root->data < k2) {
        print_range(root->right, k1, k2);
    }
}

// Find Kth smallest element
BSTNode* kth_smallest(BSTNode* root, int k, int* count) {
    if (root == NULL) return NULL;
    
    // Traverse left subtree
    BSTNode* left = kth_smallest(root->left, k, count);
    if (left != NULL) return left;
    
    // Visit current node
    (*count)++;
    if (*count == k) return root;
    
    // Traverse right subtree
    return kth_smallest(root->right, k, count);
}

// Find Kth largest element (reverse inorder)
BSTNode* kth_largest(BSTNode* root, int k, int* count) {
    if (root == NULL) return NULL;
    
    // Traverse right subtree first
    BSTNode* right = kth_largest(root->right, k, count);
    if (right != NULL) return right;
    
    // Visit current node
    (*count)++;
    if (*count == k) return root;
    
    // Traverse left subtree
    return kth_largest(root->left, k, count);
}

// Print tree structure (rotated 90 degrees)
void print_tree_structure(BSTNode* root, int space) {
    const int COUNT = 10;
    
    if (root == NULL) return;
    
    space += COUNT;
    
    print_tree_structure(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    print_tree_structure(root->left, space);
}

// Find path from root to a given node
bool path_to_node(BSTNode* root, int target, int path[], int* path_length) {
    if (root == NULL) return false;
    
    path[(*path_length)++] = root->data;
    
    if (root->data == target) return true;
    
    if ((target < root->data && path_to_node(root->left, target, path, path_length)) ||
        (target > root->data && path_to_node(root->right, target, path, path_length))) {
        return true;
    }
    
    (*path_length)--; // Backtrack
    return false;
}

// Calculate distance between two nodes
int distance_between_nodes(BSTNode* root, int n1, int n2) {
    BSTNode* lca = lowest_common_ancestor(root, n1, n2);
    if (lca == NULL) return -1;
    
    int path1[1000], path2[1000];
    int len1 = 0, len2 = 0;
    
    path_to_node(lca, n1, path1, &len1);
    path_to_node(lca, n2, path2, &len2);
    
    return (len1 - 1) + (len2 - 1); // -1 because LCA is counted in both paths
}

// Free entire tree
void free_tree(BSTNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Queue implementation for level order traversal
Queue* create_queue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(Queue* q, BSTNode* node) {
    QueueNode* new_node = malloc(sizeof(QueueNode));
    new_node->tree_node = node;
    new_node->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

BSTNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    
    QueueNode* temp = q->front;
    BSTNode* result = temp->tree_node;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return result;
}

bool is_queue_empty(Queue* q) {
    return q->front == NULL;
}

void free_queue(Queue* q) {
    while (!is_queue_empty(q)) {
        dequeue(q);
    }
    free(q);
}

// Menu-driven main function
int main() {
    BSTNode* root = NULL;
    int choice, value, k1, k2, k, n1, n2;
    
    while (1) {
        printf("\n=== Binary Search Tree Operations ===\n");
        printf("BASIC OPERATIONS:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Find Minimum\n");
        printf("5. Find Maximum\n");
        
        printf("\nTRAVERSALS:\n");
        printf("6. Inorder Traversal (sorted)\n");
        printf("7. Preorder Traversal\n");
        printf("8. Postorder Traversal\n");
        printf("9. Level Order Traversal\n");
        
        printf("\nTREE PROPERTIES:\n");
        printf("10. Height of Tree\n");
        printf("11. Count Nodes\n");
        printf("12. Validate BST\n");
        printf("13. Print Tree Structure\n");
        
        printf("\nADVANCED OPERATIONS:\n");
        printf("14. Lowest Common Ancestor\n");
        printf("15. Print Range\n");
        printf("16. Kth Smallest Element\n");
        printf("17. Kth Largest Element\n");
        printf("18. Distance Between Nodes\n");
        
        printf("\nUTILITY:\n");
        printf("19. Create Sample Tree\n");
        printf("20. Clear Tree\n");
        printf("21. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Value %d inserted.\n", value);
                break;
                
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value)) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;
                
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete_node(root, value);
                printf("Value %d deleted (if it existed).\n", value);
                break;
                
            case 4: {
                BSTNode* min_node = find_min(root);
                if (min_node) {
                    printf("Minimum value: %d\n", min_node->data);
                } else {
                    printf("Tree is empty.\n");
                }
                break;
            }
            
            case 5: {
                BSTNode* max_node = find_max(root);
                if (max_node) {
                    printf("Maximum value: %d\n", max_node->data);
                } else {
                    printf("Tree is empty.\n");
                }
                break;
            }
            
            case 6:
                printf("Inorder traversal: ");
                inorder_traversal(root);
                printf("\n");
                break;
                
            case 7:
                printf("Preorder traversal: ");
                preorder_traversal(root);
                printf("\n");
                break;
                
            case 8:
                printf("Postorder traversal: ");
                postorder_traversal(root);
                printf("\n");
                break;
                
            case 9:
                printf("Level order traversal: ");
                level_order_traversal(root);
                printf("\n");
                break;
                
            case 10:
                printf("Height of tree: %d\n", height(root));
                break;
                
            case 11:
                printf("Number of nodes: %d\n", count_nodes(root));
                break;
                
            case 12:
                if (is_valid_bst(root, INT_MIN, INT_MAX)) {
                    printf("Tree is a valid BST.\n");
                } else {
                    printf("Tree is NOT a valid BST.\n");
                }
                break;
                
            case 13:
                printf("Tree structure (rotated 90° clockwise):\n");
                print_tree_structure(root, 0);
                break;
                
            case 14:
                printf("Enter two values to find LCA: ");
                scanf("%d %d", &n1, &n2);
                {
                    BSTNode* lca = lowest_common_ancestor(root, n1, n2);
                    if (lca) {
                        printf("Lowest Common Ancestor of %d and %d is: %d\n", n1, n2, lca->data);
                    } else {
                        printf("LCA not found (tree might be empty).\n");
                    }
                }
                break;
                
            case 15:
                printf("Enter range (k1 k2): ");
                scanf("%d %d", &k1, &k2);
                printf("Nodes in range [%d, %d]: ", k1, k2);
                print_range(root, k1, k2);
                printf("\n");
                break;
                
            case 16:
                printf("Enter k for kth smallest: ");
                scanf("%d", &k);
                {
                    int count = 0;
                    BSTNode* result = kth_smallest(root, k, &count);
                    if (result) {
                        printf("%dth smallest element: %d\n", k, result->data);
                    } else {
                        printf("Tree has fewer than %d elements.\n", k);
                    }
                }
                break;
                
            case 17:
                printf("Enter k for kth largest: ");
                scanf("%d", &k);
                {
                    int count = 0;
                    BSTNode* result = kth_largest(root, k, &count);
                    if (result) {
                        printf("%dth largest element: %d\n", k, result->data);
                    } else {
                        printf("Tree has fewer than %d elements.\n", k);
                    }
                }
                break;
                
            case 18:
                printf("Enter two nodes to find distance: ");
                scanf("%d %d", &n1, &n2);
                {
                    int distance = distance_between_nodes(root, n1, n2);
                    if (distance >= 0) {
                        printf("Distance between %d and %d: %d\n", n1, n2, distance);
                    } else {
                        printf("One or both nodes not found in the tree.\n");
                    }
                }
                break;
                
            case 19:
                // Create sample tree: 50, 30, 70, 20, 40, 60, 80
                printf("Creating sample tree with values: 50, 30, 70, 20, 40, 60, 80\n");
                root = insert(root, 50);
                root = insert(root, 30);
                root = insert(root, 70);
                root = insert(root, 20);
                root = insert(root, 40);
                root = insert(root, 60);
                root = insert(root, 80);
                printf("Sample tree created.\n");
                break;
                
            case 20:
                free_tree(root);
                root = NULL;
                printf("Tree cleared.\n");
                break;
                
            case 21:
                free_tree(root);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
    
    return 0;
}
