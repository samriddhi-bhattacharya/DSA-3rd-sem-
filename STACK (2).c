#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int top;
    int maxSize;
} Stack;

Stack* createStack(int size) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    stack->arr = (int*) malloc(size * sizeof(int));
    if (!stack->arr) {
        printf("Memory allocation for stack array failed!\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->maxSize = size;
    return stack;
}

void push(Stack *stack) {
    if (stack->top == stack->maxSize - 1) {
        printf("Stack Overflow! Cannot push more elements.\n");
        return;
    }
    int val;
    printf("Enter the value to push: ");
    scanf("%d", &val);
    stack->arr[++(stack->top)] = val;
    printf("%d pushed to stack.\n", val);
}

void pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }
    printf("%d popped from stack.\n", stack->arr[(stack->top)--]);
}

void display(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->arr[i]);
    }
}

void freeStack(Stack *stack) {
    free(stack->arr);
    free(stack);
}

int main() {
    int size;
    printf("Enter stack size: ");
    scanf("%d", &size);

    Stack *stack = createStack(size);

    int choice;
    do {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: push(stack); break;
            case 2: pop(stack); break;
            case 3: display(stack); break;
            case 4: printf("Exiting program.\n"); break;
            default: printf("Invalid choice! Please enter a valid option.\n");
        }
    } while(choice != 4);

    freeStack(stack);
    return 0;
}

