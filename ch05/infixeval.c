#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_STACK_SIZE 100  // stack size
#define MAX_EXPR_SIZE 100   // expression size 

typedef enum {lparen, rparen, plus, minus, times, divide, 
    mod, eos, operand} precedence;

precedence stack[MAX_STACK_SIZE];   // 연산자 스택
int op_stack[MAX_STACK_SIZE];       // 피연산자 스택
int top = -1;                       // 연산자 스택 초기화
int op_top = -1;                    // 피연산자 스택 초기화
char expr[MAX_EXPR_SIZE];           // 입력식 
char postfix_expr[MAX_EXPR_SIZE];   // 후위 표기식

// 연산자 스택 push 함수 
void push(precedence p) {
    stack[++top] = p;
}
// 연산자 스택 pop 함수 
precedence pop() {
    return stack[top--];
}

// 피연산자 스택 push 함수 
void op_push(int value) {
    op_stack[++op_top] = value;
}
// 피연산자 스택 pop 함수 
int op_pop() {
    return op_stack[op_top--];
}

// stack operator 우선순위 
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
// token operator 우선순위 
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
        case '\0': return eos;
        default : return operand;
    }
}

// precedence를 char로 변환 
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
    int size = 0;

    push(eos);

    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
        if (token == operand) {             // 피연산자
            postfix_expr[size++] = symbol;  // 피연산자는 바로 후위 표기식에 저장
        }
        else if (token == rparen) {         // ( 괄호
            while (stack[top] != lparen)    // 왼쪽 괄호가 나올 때까지 스택에서 pop
                postfix_expr[size++] = print_token(pop());  
            pop();                          // 왼쪽 괄호 제거
        } 
        else {
            while (isp[stack[top]] >= icp[token])   // 스택의 우선순위가 더 크거나 같으면 pop
                postfix_expr[size++] = print_token(pop());  
            push(token); 
        }
    }
    while ((token = pop()) != eos)
        postfix_expr[size++] = print_token(token);  // 나머지 연산자 모두 pop

    postfix_expr[size] = '\0';  
}

// 입력에서 후위 표기식 토큰 받아들이기 
precedence get_postfix_token(char *symbol, int *n) {
    *symbol = postfix_expr[(*n)++];
    switch (*symbol) {
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod; 
        case '\0': return eos;
        default : return operand;
    }
}

// 후위 표기식 연산 
int eval(void) {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;

    token = get_postfix_token(&symbol, &n);
    while (token != eos) {
        if (token == operand) {
            op_push(symbol - '0');  // 피연산자를 연산 스택에 push
        } else {
            op2 = op_pop();
            op1 = op_pop();
            switch (token) {
                case plus: op_push(op1 + op2); break;
                case minus: op_push(op1 - op2); break;
                case times: op_push(op1 * op2); break;
                case divide: op_push(op1 / op2); break;
                case mod: op_push(op1 % op2); break;
            }
        }
        token = get_postfix_token(&symbol, &n);
    }
    return op_pop();  // 최종 결과 반환
}

int infixeval(void) {
    postfix();  // 중위 표기식 -> 후위 표기식 변환
    return eval();  // 후위 표기식 연산
}

int main() {
    int result;
    strcpy(expr, "(5/(6-3+2))*(7-8)*2");
    result = infixeval();
    printf("결과값은 %d\n", result);
    return 0;
}
