#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int top;
    int capacity;
    char** array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char**)malloc(capacity * sizeof(char*));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char* str) {
    stack->array[++stack->top] = str;
}

char* pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void prefixToPostfix(char* prefix, char* postfix) {
    int len = strlen(prefix);
    struct Stack* stack = createStack(len);
    for (int i = len - 1; i >= 0; i--) {
        if (isOperator(prefix[i])) {
            char* op1 = pop(stack);
            char* op2 = pop(stack);
            char* expr = (char*)malloc(strlen(op1) + strlen(op2) + 2);
            sprintf(expr, "%s%s%c", op1, op2, prefix[i]);
            push(stack, expr);
        } else {
            char* operand = (char*)malloc(2);
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
    }
    strcpy(postfix, pop(stack));
}

int main() {
    char prefix[100], postfix[100];
    printf("Enter your INFIX Expression:\n");
    scanf("%s", prefix);
    prefixToPostfix(prefix, postfix);
    printf("%s\n", postfix);
    return 0;
}
