#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <string.h>


int get_token(char *token, int *n) {

    char symbol = token[*n];

    *n = *n + 1;

    switch (symbol) {
        case '(' : return 1;
        case ')' : return 2;
        case '+' : return 3;
        case '-' : return 4;
        case '/' : return 5;
        case '*' : return 6;
        case '%' : return 7;
        case ' ' : return 8;
        default : return 9;
    }
}

// stack 생성 & 초기화 
char op_stack[10];
int top = -1;
// push
void push(char op) {
    op_stack[++top] = op;
}
// pop 
char pop() {
    return op_stack[top--];
}

int main()
{
    char myexpr[10];
    int token = 0;
    int n = 0;
    strcpy(myexpr, "3+2*5-4 "); // 공백 (eos)

    /*
    for ( ; token!=8; ) { // token 8은 eos 
        token = get_token(myexpr, &n); // &n : 함수 내부에서 변화 생기면 n에도 영향 
        if (token == 9) printf("%s ", "operand"); // token 9는 피연산자
        else if (token == 8) printf(" ");
        else printf("%s ", "operator");
    }
    */

    for ( ; token!=8; ) { // token 8은 eos 
        token = get_token(myexpr, &n); // &n : 함수 내부에서 변화 생기면 n에도 영향 
        if (token == 9) printf("%c ", myexpr[n-1]);
        else if (token == 8) printf("");
        else push(myexpr[n-1]);
    }

    while (top > -1) {
        printf("%c ", pop());
    }

    printf("\n");

    // 출력 : operand operator operand operator operand operator operand

}