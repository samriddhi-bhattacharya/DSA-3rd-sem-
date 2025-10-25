#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
struct Node* head = NULL;


void insert(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    printf("Inserted %d into the circular linked list.\n", value);
}


void delete(int value) {
    if (head == NULL) {
        printf("The list is empty. Deletion not possible.\n");
        return;
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    
    if (head->data == value) {
        while (temp->next != head) {
            temp = temp->next;
        }
        if (head->next == head) { 
            free(head);
            head = NULL;
        } else {
            temp->next = head->next;
            free(head);
            head = temp->next;
        }
        printf("Deleted %d from the circular linked list.\n", value);
        return;
    }

    
    do {
        prev = temp;
        temp = temp->next;
        if (temp->data == value) {
            prev->next = temp->next;
            free(temp);
            printf("Deleted %d from the circular linked list.\n", value);
            return;
        }
    } while (temp != head);

    printf("Value %d not found in the list.\n", value);
}


void display() {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}


int main() {
    int choice, value;

    while (1) {
        printf("\nCircular Linked List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                delete(value);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}