#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_STACK_SIZE 100  // stack size
#define MAX_EXPR_SIZE 100   // expression size 

// enum : 열거형 데이터 타입 
typedef enum {lparen, rparen, plus, minus, times, divide, 
    mod, eos, operand} precedence;

precedence stack[MAX_STACK_SIZE];   // stack 선언
int top = -1;                       // stack 초기화
char expr[MAX_EXPR_SIZE];           // expression

// push 함수
void push(precedence p) {
    stack[++top]=p;
}
// pop 함수 
precedence pop() {
    return stack[top--];
}

// stack operator 우선순위 : stack에 ( 가 있으면 push -> 우선 순위 0
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
// token operator 우선순위 : ( 가 입력되면 무조건 push -> 우선 순위 20 
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

// 입력에서 토큰 받아들이기 
precedence get_token(char *symbol, int *n) {

    *symbol = expr[(*n)++];

    switch (*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod; 
        case ' ' : return eos;
        default : return operand;
    }
}

char print_token(precedence token) {
    switch (token) {
        case plus : return '+';
        case minus : return '-';
        case times : return '*';
        case divide : return '/';
        case mod : return '%';
        default : return ' ';
    }
}

// 중위 표기를 후위 표기로 
void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    push(eos);

    for(token = get_token(&symbol, &n); token!=eos; token = get_token(&symbol, &n)) {
        if(token == operand) printf("%c", symbol);
        else if(token == rparen) {
            while(stack[top] != lparen)
                printf("%c",print_token(pop()));
            pop();}
        else { while(isp[stack[top]] >= icp[token])
                    printf("%c",print_token(pop()));
                push(token); }
    }
    while((token = pop()) != eos)
        printf("%c ",print_token(token));
    printf("\n");
}

int main()
{
    strcpy(expr, "3+2*5-4 "); // 공백 (eos)
    postfix();
    return 0;
}