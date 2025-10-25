#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void push(int *stack, int *top, int x) {
    stack[++(*top)]=x;
}
int pop(int *stack, int *top) {
    return stack[(*top)--];
}
int evaluatePostfix(char *exp) {
    int stack[100], top=-1, i=0;
    while(exp[i]) {
        if(isdigit(exp[i])) {
            int num=0;
            while(isdigit(exp[i])) {
                num =  num * 10 + (exp[i++] - '0');
            }
            push(stack, &top, num);
        } else if (exp[i]== ' ' || exp[i]== '\t') {
            i++;
        }
        else{
            int b= pop(stack, &top);
            int a =pop(stack, &top);
            switch(exp[i++]) {
                case '+' : push(stack, &top, a+b); break;
                case '-' : push(stack, &top, a-b); break;
                case '*' : push(stack, &top, a*b); break;
                case '/' : push(stack, &top, a/b); break;
            }
        }
    }
    return pop(stack, &top);
}
int main() {
    char exp[100];
    printf("Enter a postfix expression: ");
    fgets(exp, 100, stdin);
    exp[strcspn(exp, "\n")] = 0;
    printf("Postfix expression: %s\n", exp);
    printf("Result: %d\n", evaluatePostfix(exp));
    return 0;
}