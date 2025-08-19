#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Doubly linked list node
typedef struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
} DNode;

// Function prototypes
Node* create_node(int data);
void insert_at_beginning(Node** head, int data);
void insert_at_end(Node** head, int data);
void insert_at_position(Node** head, int data, int position);
void delete_by_value(Node** head, int data);
void delete_at_position(Node** head, int position);
Node* search(Node* head, int data);
void reverse_list(Node** head);
void display_list(Node* head);
void free_list(Node** head);
int get_length(Node* head);
Node* get_middle(Node* head);
void remove_duplicates(Node* head);
Node* merge_sorted_lists(Node* list1, Node* list2);
int has_cycle(Node* head);

// Doubly linked list functions
DNode* create_dnode(int data);
void insert_at_beginning_doubly(DNode** head, int data);
void insert_at_end_doubly(DNode** head, int data);
void delete_by_value_doubly(DNode** head, int data);
void display_list_forward(DNode* head);
void display_list_backward(DNode* head);
void free_doubly_list(DNode** head);

// Create a new node
Node* create_node(int data) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert at the beginning
void insert_at_beginning(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
    printf("Inserted %d at the beginning.\n", data);
}

// Insert at the end
void insert_at_end(Node** head, int data) {
    Node* new_node = create_node(data);
    
    if (*head == NULL) {
        *head = new_node;
        printf("Inserted %d as the first element.\n", data);
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    printf("Inserted %d at the end.\n", data);
}

// Insert at specific position (0-based indexing)
void insert_at_position(Node** head, int data, int position) {
    if (position < 0) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 0) {
        insert_at_beginning(head, data);
        return;
    }
    
    Node* new_node = create_node(data);
    Node* current = *head;
    
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Position %d is out of bounds!\n", position);
        free(new_node);
        return;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    printf("Inserted %d at position %d.\n", data, position);
}

// Delete by value (first occurrence)
void delete_by_value(Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    // If head node contains the data
    if ((*head)->data == data) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Deleted %d from the list.\n", data);
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("Element %d not found in the list!\n", data);
        return;
    }
    
    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    printf("Deleted %d from the list.\n", data);
}

// Delete at specific position
void delete_at_position(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    if (position < 0) {
        printf("Invalid position!\n");
        return;
    }
    
    // Delete head
    if (position == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        printf("Deleted element %d at position %d.\n", temp->data, position);
        free(temp);
        return;
    }
    
    Node* current = *head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("Position %d is out of bounds!\n", position);
        return;
    }
    
    Node* temp = current->next;
    current->next = current->next->next;
    printf("Deleted element %d at position %d.\n", temp->data, position);
    free(temp);
}

// Search for an element
Node* search(Node* head, int data) {
    Node* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == data) {
            printf("Element %d found at position %d.\n", data, position);
            return current;
        }
        current = current->next;
        position++;
    }
    
    printf("Element %d not found in the list.\n", data);
    return NULL;
}

// Reverse the linked list
void reverse_list(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    *head = prev;
    printf("List reversed successfully.\n");
}

// Display the list
void display_list(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    printf("List: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Get length of the list
int get_length(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Find middle element (Floyd's algorithm)
Node* get_middle(Node* head) {
    if (head == NULL) return NULL;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// Remove duplicates from sorted list
void remove_duplicates(Node* head) {
    if (head == NULL) return;
    
    Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    printf("Duplicates removed from sorted list.\n");
}

// Merge two sorted lists
Node* merge_sorted_lists(Node* list1, Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    
    Node* result = NULL;
    
    if (list1->data <= list2->data) {
        result = list1;
        result->next = merge_sorted_lists(list1->next, list2);
    } else {
        result = list2;
        result->next = merge_sorted_lists(list1, list2->next);
    }
    
    return result;
}

// Detect cycle in linked list (Floyd's algorithm)
int has_cycle(Node* head) {
    if (head == NULL) return 0;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return 1; // Cycle detected
        }
    }
    
    return 0; // No cycle
}

// Free the entire list
void free_list(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("List memory freed.\n");
}

// Doubly Linked List Functions

DNode* create_dnode(int data) {
    DNode* new_node = malloc(sizeof(DNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert_at_beginning_doubly(DNode** head, int data) {
    DNode* new_node = create_dnode(data);
    
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    new_node->next = *head;
    *head = new_node;
    printf("Inserted %d at the beginning (doubly).\n", data);
}

void insert_at_end_doubly(DNode** head, int data) {
    DNode* new_node = create_dnode(data);
    
    if (*head == NULL) {
        *head = new_node;
        printf("Inserted %d as the first element (doubly).\n", data);
        return;
    }
    
    DNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
    printf("Inserted %d at the end (doubly).\n", data);
}

void delete_by_value_doubly(DNode** head, int data) {
    if (*head == NULL) {
        printf("Doubly list is empty!\n");
        return;
    }
    
    DNode* current = *head;
    
    // Find the node to delete
    while (current != NULL && current->data != data) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Element %d not found in doubly list!\n", data);
        return;
    }
    
    // Update links
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next; // Deleting head
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
    printf("Deleted %d from doubly list.\n", data);
}

void display_list_forward(DNode* head) {
    if (head == NULL) {
        printf("Doubly list is empty.\n");
        return;
    }
    
    printf("Forward: ");
    DNode* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf(" <-> NULL\n");
}

void display_list_backward(DNode* head) {
    if (head == NULL) {
        printf("Doubly list is empty.\n");
        return;
    }
    
    // Go to the last node
    DNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    printf("Backward: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(" <-> ");
        }
        current = current->prev;
    }
    printf(" <-> NULL\n");
}

void free_doubly_list(DNode** head) {
    DNode* current = *head;
    while (current != NULL) {
        DNode* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("Doubly list memory freed.\n");
}

// Menu-driven program
int main() {
    Node* singly_list = NULL;
    DNode* doubly_list = NULL;
    int choice, data, position;
    
    while (1) {
        printf("\n=== Linked List Operations ===\n");
        printf("SINGLY LINKED LIST:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete by value\n");
        printf("5. Delete at position\n");
        printf("6. Search element\n");
        printf("7. Reverse list\n");
        printf("8. Display list\n");
        printf("9. Get length\n");
        printf("10. Find middle element\n");
        printf("11. Remove duplicates (sorted list)\n");
        printf("12. Check for cycle\n");
        
        printf("\nDOUBLY LINKED LIST:\n");
        printf("13. Insert at beginning (doubly)\n");
        printf("14. Insert at end (doubly)\n");
        printf("15. Delete by value (doubly)\n");
        printf("16. Display forward (doubly)\n");
        printf("17. Display backward (doubly)\n");
        
        printf("\nOTHER:\n");
        printf("18. Free all memory and exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_beginning(&singly_list, data);
                break;
                
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_end(&singly_list, data);
                break;
                
            case 3:
                printf("Enter data and position: ");
                scanf("%d %d", &data, &position);
                insert_at_position(&singly_list, data, position);
                break;
                
            case 4:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                delete_by_value(&singly_list, data);
                break;
                
            case 5:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                delete_at_position(&singly_list, position);
                break;
                
            case 6:
                printf("Enter data to search: ");
                scanf("%d", &data);
                search(singly_list, data);
                break;
                
            case 7:
                reverse_list(&singly_list);
                break;
                
            case 8:
                display_list(singly_list);
                break;
                
            case 9:
                printf("Length of list: %d\n", get_length(singly_list));
                break;
                
            case 10: {
                Node* middle = get_middle(singly_list);
                if (middle) {
                    printf("Middle element: %d\n", middle->data);
                } else {
                    printf("List is empty!\n");
                }
                break;
            }
            
            case 11:
                remove_duplicates(singly_list);
                break;
                
            case 12:
                if (has_cycle(singly_list)) {
                    printf("Cycle detected in the list!\n");
                } else {
                    printf("No cycle detected in the list.\n");
                }
                break;
                
            case 13:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_beginning_doubly(&doubly_list, data);
                break;
                
            case 14:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_at_end_doubly(&doubly_list, data);
                break;
                
            case 15:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                delete_by_value_doubly(&doubly_list, data);
                break;
                
            case 16:
                display_list_forward(doubly_list);
                break;
                
            case 17:
                display_list_backward(doubly_list);
                break;
                
            case 18:
                free_list(&singly_list);
                free_doubly_list(&doubly_list);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
    
    return 0;
}
