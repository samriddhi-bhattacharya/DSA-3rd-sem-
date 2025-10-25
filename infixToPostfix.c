#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int top;
    int capacity;
    char* array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(capacity * sizeof(char));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    if (!isFull(stack)) stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack)) return stack->array[stack->top--];
    return '\0';
}

char peek(struct Stack* stack) {
    if (!isEmpty(stack)) return stack->array[stack->top];
    return '\0';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isAlphaNum(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, k = 0;
    for (i = 0; infix[i]; i++) {
        if (isAlphaNum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[k++] = pop(stack);
            pop(stack);
        } else {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(infix[i]))
                postfix[k++] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
        postfix[k++] = pop(stack);
    postfix[k] = '\0';
    free(stack->array);
    free(stack);
}

int main() {
    char infix[100], postfix[100];
    printf("Enter your infix expression: \n");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);
    return 0;
}
