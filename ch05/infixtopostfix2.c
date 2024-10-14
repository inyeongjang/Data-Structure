// precedence 타입을 사용하지 않고 작성하기

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_STACK_SIZE 100  // stack size
#define MAX_EXPR_SIZE 100   // expression size 

int stack[MAX_STACK_SIZE];   // stack 선언
int top = -1;                // stack 초기화
char in_expr[MAX_EXPR_SIZE];    // 입력 문자열
char post_expr[MAX_EXPR_SIZE];  // 출력 문자열 
int m = 0;
char op[] = {'(', ')', '+', '-', '*', '/', '%', ' '};
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

void print_stack() {
    printf("Stack 출력 : ");
    for (int i=top; i>-1; i--) {
        printf("%c ", op[stack[i]]);
    }
    printf("\n");
}

void push(int p) {
    stack[++top]=p;
}

int pop() {
    int i=stack[top--];
    return i;
}

int get_token(char *symbol, int *n) {

    *symbol = in_expr[(*n)++];

    switch (*symbol) {
        case '(' : return 0;
        case ')' : return 1;
        case '+' : return 2;
        case '-' : return 3;
        case '/' : return 4;
        case '*' : return 5;
        case '%' : return 6; 
        case ' ' : return 7;
        default : return 8;
    }
}

void postfix(void) {
    char symbol;
    int token;
    int n = 0;
    push(7);

    for(token = get_token(&symbol, &n); token != 7; token = get_token(&symbol, &n)) {
        if(token == 8) post_expr[m++] = symbol;
        else if(token == 1) {
            while(stack[top] != 0)
                post_expr[m++] = op[pop()];
            pop();}
        else { while(isp[stack[top]] >= icp[token])
                    post_expr[m++] = op[pop()];
                push(token); }
        print_stack();
    }
    while((token = pop()) != 7)
        post_expr[m++] =op[token];
}

int main()
{
    strcpy(in_expr, "3+2*5-4 "); // 공백 (eos)
    postfix();
    printf("Postfix_express : %s", post_expr);
    return 0;
}