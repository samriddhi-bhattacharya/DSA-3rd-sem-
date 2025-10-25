#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char data[16];
    struct Node* left;
    struct Node* right;
} Node;


typedef struct {
    Node** array;
    int top;
    int capacity;
} StackNodePtr;

StackNodePtr createStackNodePtr(int capacity) {
    StackNodePtr stack;
    stack.array = (Node**)malloc(sizeof(Node*) * capacity);
    if (!stack.array) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    stack.top = -1;
    stack.capacity = capacity;
    return stack;
}

void pushNode(StackNodePtr* stack, Node* node) {
    if (stack->top >= stack->capacity - 1) {
        printf("Stack overflow.\n");
        exit(1);
    }
    stack->array[++(stack->top)] = node;
}

Node* popNode(StackNodePtr* stack) {
    if (stack->top < 0) {
        printf("Stack underflow.\n");
        exit(1);
    }
    return stack->array[(stack->top)--];
}

void freeStackNodePtr(StackNodePtr* stack) {
    free(stack->array);
}


typedef struct {
    char* array;
    int top;
    int capacity;
} StackChar;

StackChar createStackChar(int capacity) {
    StackChar stack;
    stack.array = (char*)malloc(sizeof(char) * capacity);
    if (!stack.array) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    stack.top = -1;
    stack.capacity = capacity;
    return stack;
}

void pushChar(StackChar* stack, char ch) {
    if (stack->top >= stack->capacity - 1) {
        printf("Stack overflow.\n");
        exit(1);
    }
    stack->array[++(stack->top)] = ch;
}

char popChar(StackChar* stack) {
    if (stack->top < 0) {
        printf("Stack underflow.\n");
        exit(1);
    }
    return stack->array[(stack->top)--];
}

char peekChar(StackChar* stack) {
    if (stack->top < 0) return '\0';
    return stack->array[stack->top];
}

void freeStackChar(StackChar* stack) {
    free(stack->array);
}


int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

int isOperatorChar(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


void infixToPostfix(const char* infix, char* postfix) {
    StackChar stack = createStackChar(100);
    int i = 0, k = 0;
    int len = strlen(infix);
    char token[16];

    while (i < len) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }
        if (isdigit(infix[i])) {
            
            int t = 0;
            while (i < len && isdigit(infix[i])) {
                token[t++] = infix[i++];
            }
            token[t] = '\0';
            
            for (int j = 0; j < t; j++)
                postfix[k++] = token[j];
            postfix[k++] = ' ';
        } else if (infix[i] == '(') {
            pushChar(&stack, infix[i]);
            i++;
        } else if (infix[i] == ')') {
            while (peekChar(&stack) != '(') {
                postfix[k++] = popChar(&stack);
                postfix[k++] = ' ';
            }
            popChar(&stack); 
            i++;
        } else if (isOperatorChar(infix[i])) {
            while (stack.top != -1 && precedence(peekChar(&stack)) >= precedence(infix[i])) {
                postfix[k++] = popChar(&stack);
                postfix[k++] = ' ';
            }
            pushChar(&stack, infix[i]);
            i++;
        } else {
            printf("Invalid character in expression: %c\n", infix[i]);
            freeStackChar(&stack);
            exit(1);
        }
    }
    while (stack.top != -1) {
        postfix[k++] = popChar(&stack);
        postfix[k++] = ' ';
    }
    if (k > 0) k--; 
    postfix[k] = '\0';

    freeStackChar(&stack);
}


Node* createNode(const char* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(node->data, data);
    node->left = node->right = NULL;
    return node;
}

int isOperator(const char* token) {
    return strlen(token) == 1 && isOperatorChar(token[0]);
}


Node* buildExpressionTree(const char* postfix) {
    char expr[256];
    strcpy(expr, postfix);

    StackNodePtr stack = createStackNodePtr(100);

    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (!isOperator(token)) {
            Node* operand = createNode(token);
            pushNode(&stack, operand);
        } else {
            Node* opNode = createNode(token);
            opNode->right = popNode(&stack);
            opNode->left = popNode(&stack);
            pushNode(&stack, opNode);
        }
        token = strtok(NULL, " ");
    }
    Node* root = popNode(&stack);
    freeStackNodePtr(&stack);
    return root;
}


void printInfix(Node* root) {
    if (root) {
        int op = isOperator(root->data);
        if (op) printf("(");
        printInfix(root->left);
        printf("%s", root->data);
        printInfix(root->right);
        if (op) printf(")");
    }
}

void printPrefix(Node* root) {
    if (!root) return;
    printf("%s ", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}

void printPostfix(Node* root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%s ", root->data);
}


int evaluate(Node* root) {
    if (!root->left && !root->right) {
        return atoi(root->data);
    }
    int left = evaluate(root->left);
    int right = evaluate(root->right);
    switch (root->data[0]) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default:
            printf("Unknown operator: %s\n", root->data);
            exit(1);
    }
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char infix[256];
    printf("Enter an infix expression (integers and + - * /, parentheses allowed):\n");
    if (!fgets(infix, sizeof(infix), stdin)) {
        printf("Input error.\n");
        return 1;
    }
    size_t len = strlen(infix);
    if (len > 0 && infix[len-1] == '\n')
        infix[len-1] = '\0';

    char postfix[512];
    infixToPostfix(infix, postfix);

    Node* root = buildExpressionTree(postfix);

    printf("Infix expression: ");
    printInfix(root);
    printf("\n");

    printf("Prefix expression: ");
    printPrefix(root);
    printf("\n");

    printf("Postfix expression: ");
    printPostfix(root);
    printf("\n");

    int val = evaluate(root);
    printf("Evaluated result: %d\n", val);

    freeTree(root);
    return 0;
}



