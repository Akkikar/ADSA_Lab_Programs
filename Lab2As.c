#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} CharStack;

typedef struct {
    int items[MAX];
    int top;
} IntStack;

void initCharStack(CharStack *s) {
    s->top = -1;
}

int isEmptyChar(CharStack *s) {
    return s->top == -1;
}

void pushChar(CharStack *s, char ch) {
    if (s->top < MAX - 1)
        s->items[++s->top] = ch;
}

char popChar(CharStack *s) {
    if (!isEmptyChar(s))
        return s->items[s->top--];

    return '\0';
}

char peekChar(CharStack *s) {
    if (!isEmptyChar(s))
        return s->items[s->top];

    return '\0';
}

void initIntStack(IntStack *s) {
    s->top = -1;
}

void pushInt(IntStack *s, int value) {
    if (s->top < MAX - 1)
        s->items[++s->top] = value;
}

int popInt(IntStack *s) {
    if (s->top >= 0)
        return s->items[s->top--];

    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    CharStack s;
    initCharStack(&s);

    int i = 0;
    int k = 0;

    while (infix[i] != '\0') {

        
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }

            postfix[k++] = ' ';
        }

        
        else if (infix[i] == '(') {
            pushChar(&s, infix[i]);
            i++;
        }

        else if (infix[i] == ')') {

            while (!isEmptyChar(&s) && peekChar(&s) != '(') {
                postfix[k++] = popChar(&s);
                postfix[k++] = ' ';
            }

            if (!isEmptyChar(&s))
                popChar(&s);   

            i++;
        }

    
        else if (isOperator(infix[i])) {

            while (!isEmptyChar(&s) &&
                   peekChar(&s) != '(' &&
                   precedence(peekChar(&s)) >= precedence(infix[i])) {

                postfix[k++] = popChar(&s);
                postfix[k++] = ' ';
            }

            pushChar(&s, infix[i]);
            i++;
        }

        else {
            i++;
        }
    }

  
    while (!isEmptyChar(&s)) {
        postfix[k++] = popChar(&s);
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}


int evaluatePostfix(char *postfix) {
    IntStack s;
    initIntStack(&s);

    int i = 0;

    while (postfix[i] != '\0') {

       
        if (isspace(postfix[i])) {
            i++;
            continue;
        }

      
        if (isdigit(postfix[i])) {

            int number = 0;

            while (isdigit(postfix[i])) {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }

            pushInt(&s, number);
        }

      
        else if (isOperator(postfix[i])) {

            int b = popInt(&s);
            int a = popInt(&s);
            int result = 0;

            switch (postfix[i]) {

                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }

                    result = a / b;
                    break;
            }

            pushInt(&s, result);
            i++;
        }

        else {
            i++;
        }
    }

    return popInt(&s);
}

int main() {

    char infix[MAX];
    char postfix[MAX * 2];

    printf("Enter expression: ");

  
    fgets(infix, MAX, stdin);

    
    infix[strcspn(infix, "\n")] = '\0';

   
    infixToPostfix(infix, postfix);

   
    int result = evaluatePostfix(postfix);

    printf("%d\n", result);

    return 0;
}
