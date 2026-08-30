#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX 20

typedef struct{
    char items[MAX];
    int top;
}Stack;

void initStack(Stack *s){
    s->top=-1;
}

int isEmpty(Stack *s){
    return s->top==-1;
}

void push(Stack *s,char ch){
    if(s->top<19){
        s->items[++(s->top)]=ch;
    }
}

char pop(Stack *s){
    if(!isEmpty(s)){
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s){
    if(!isEmpty(s)){
        return s->items[s->top];
    }
    return '\0';
}

int precedence(char op){
    if(op=='*' || op=='/') return 2;
    if(op=='+' || op=='-') return 1;
    return 0;
}

int isOperator(char ch){
    return ch=='*' || ch=='/' || ch=='+' || ch=='-';
}

void InfixToPostfix(const char* infix,char* postfix){
    Stack s;
    initStack(&s);
    int k=0;
    for(int i=0;infix[i]!='\0';i++){
        char ch=infix[i];
        if(isspace(ch)) continue;
        if(isalnum(ch)){
            postfix[k++]=ch;
        }
        else if(ch=='('){
            push(&s,ch);
        }
        else if(ch==')'){
            while(!isEmpty(&s) && peek(&s)!='('){
                postfix[k++]=pop(&s);
            }
            pop(&s);
        }
        else if(isOperator(ch)){
            while(!isEmpty(&s) && isOperator(peek(&s)) && precedence(peek(&s))>=precedence(ch)){
                postfix[k++]=pop(&s);
            }
            push(&s,ch);
        }
    }
    while(!isEmpty(&s)){
        postfix[k++]=pop(&s);
    }
    postfix[k]='\0';
}

int main(){
    char infix[]="a*(b+c)/d";
    char postfix[20];
    InfixToPostfix(infix,postfix);
    printf("%s",postfix);
}