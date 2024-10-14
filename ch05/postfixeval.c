#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_STACK_SIZE 100  // stack size
#define MAX_EXPR_SIZE 100   // expression size 

typedef enum {lparen, rparen, plus, minus, times, divide, 
    mod, eos, operand} precedence;

precedence stack[MAX_STACK_SIZE];   // stack 선언
int top = -1;                       // stack 초기화
char expr[MAX_EXPR_SIZE];           // expression

// push 함수
void push(int n) {
    stack[++top]=n;
}
// pop 함수 
precedence pop() {
    return stack[top--];
}

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

int eval(void)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    int top = -1;

    token = get_token(&symbol, &n);
    while (token != eos) {
        if(token == operand)
            push(symbol-'0');
        else {
            op2 = pop();
            op1 = pop();
            switch(token) {
                case plus: push(op1 + op2);
                break;
                case minus: push(op1 - op2);
                break;
                case times: push(op1 * op2);
                break;
                case divide: push(op1 / op2);
                break;
                case mod: push(op1 % op2);
            }
        }
        token = get_token(&symbol, &n);
    }
    return pop();
}

int main(void)
{
    int result;
    strcpy(expr, "82/3-32*+ ");
    printf("후위표기식은 %s \n", expr);
    result = eval();
    printf("결과값은 %d\n", result);
    return 0;
}