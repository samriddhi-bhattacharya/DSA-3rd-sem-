
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;
typedef struct Stack {
    Node **arr;
    int top;
    int capacity;
} Stack;
Stack* createStack(int capacity) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (Node**) malloc(capacity * sizeof(Node*));
    return stack;
}
int isEmpty(Stack *stack) {
    return stack->top == -1;
}
void push(Stack *stack, Node *node) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->arr = (Node**) realloc(stack->arr, stack->capacity * sizeof(Node*));
    }
    stack->arr[++stack->top] = node;
}
Node* pop(Stack *stack) {
    if (isEmpty(stack)) return NULL;
    return stack->arr[stack->top--];
}
Node* newNode(int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
Node* insert(Node *root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}
void preorder(Node *root) {
    if (root == NULL) return;
    Stack *stack = createStack(100);
    push(stack, root);
    printf("PREORDER TRAVERSAL\n");
    while (!isEmpty(stack)) {
        Node *curr = pop(stack);
        printf("%d ", curr->data);
        if (curr->right) push(stack, curr->right);
        if (curr->left) push(stack, curr->left);
    }
    printf("\n");
    free(stack->arr);
    free(stack);
}
void inorder(Node *root) {
    Stack *stack = createStack(100);
    Node *curr = root;
    printf("INORDER TRAVERSAL\n");
    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            push(stack, curr);
            curr = curr->left;
        }
        curr = pop(stack);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
    free(stack->arr);
    free(stack);
}
void postorder(Node *root) {
    if (root == NULL) return;
    Stack *stack = createStack(100);
    Stack *output = createStack(100);
    push(stack, root);
    printf("POSTORDER TRAVERSAL\n");
    while (!isEmpty(stack)) {
        Node *curr = pop(stack);
        push(output, curr);
        if (curr->left) push(stack, curr->left);
        if (curr->right) push(stack, curr->right);
    }
    while (!isEmpty(output)) {
        Node *curr = pop(output);
        printf("%d ", curr->data);
    }
    printf("\n");
    free(stack->arr);
    free(stack);
    free(output->arr);
    free(output);
}
int main() {
    Node *root = NULL;
    int n, value;
    printf("Enter number of nodes to insert in BST: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &value);
        root = insert(root, value);
    }
    preorder(root);
    inorder(root);
    postorder(root);
    return 0;
}

