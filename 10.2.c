#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Queue structure for level order traversal
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*) malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    QueueNode* temp = q->front;
    Node* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

// Insert a node into the binary tree at first empty position (level order)
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        Node* temp = dequeue(q);
        if (temp->left == NULL) {
            temp->left = newNode;
            freeQueue(q);
            return root;
        } else {
            enqueue(q, temp->left);
        }
        if (temp->right == NULL) {
            temp->right = newNode;
            freeQueue(q);
            return root;
        } else {
            enqueue(q, temp->right);
        }
    }
    freeQueue(q);
    return root;
}

// Find and return the deepest rightmost node and its parent
void findDeepestRightmost(Node* root, Node** deepest, Node** parent) {
    if (!root) return;

    Queue* q = createQueue();
    enqueue(q, root);

    *deepest = NULL;
    *parent = NULL;
    Node* temp;
    Node* prev = NULL;

    while (!isEmpty(q)) {
        temp = dequeue(q);
        if (temp->left) {
            enqueue(q, temp->left);
            prev = temp;
        }
        if (temp->right) {
            enqueue(q, temp->right);
            prev = temp;
        }
        *deepest = temp;
    }
    *parent = prev;
    freeQueue(q);
}

// Delete node with given data
Node* deleteNode(Node* root, int data) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->data == data) {
            free(root);
            return NULL;
        } else {
            return root;
        }
    }

    Queue* q = createQueue();
    enqueue(q, root);

    Node *keyNode = NULL;
    Node* temp;

    // Find the node with the data and also the deepest rightmost node
    while (!isEmpty(q)) {
        temp = dequeue(q);
        if (temp->data == data) {
            keyNode = temp;
        }
        if (temp->left) enqueue(q, temp->left);
        if (temp->right) enqueue(q, temp->right);
    }

    if (keyNode != NULL) {
        // Find deepest rightmost node again
        Node *deepest = NULL, *parent = NULL;
        findDeepestRightmost(root, &deepest, &parent);

        if (deepest != NULL) {
            keyNode->data = deepest->data;

            // Remove the deepest rightmost node
            if (parent != NULL) {
                if (parent->right == deepest) {
                    parent->right = NULL;
                } else if (parent->left == deepest) {
                    parent->left = NULL;
                }
            } else {
                // If parent is NULL means root is the only node, handled above
            }
            free(deepest);
        }
    }

    freeQueue(q);
    return root;
}

// Traversals
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    Node* root = NULL;
    int choice, val;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder traversal\n");
        printf("4. Preorder traversal\n");
        printf("5. Postorder traversal\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;

            case 3:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

