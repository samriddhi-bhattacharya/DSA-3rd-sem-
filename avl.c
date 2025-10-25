#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}


Node* insert(Node* node, int key) {
    if (!node) return createNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


void preorder(Node* node) {
    if (node) {
        printf("%d ", node->key);
        preorder(node->left);
        preorder(node->right);
    }
}

int main() {
    Node* root = NULL;
    int n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Preorder traversal: ");
    preorder(root);

    printf("\nEnter a key to delete: ");
    scanf("%d", &key);
    root = deleteNode(root, key);

    printf("Preorder after deletion: ");
    preorder(root);
    printf("\n");

    return 0;
}

