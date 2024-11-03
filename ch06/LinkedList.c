#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 노드 생성 */
typedef struct _Node{   // _Node 구조체 정의 
    char data[10];      // 데이터 부분
    struct _Node* link; // 링크 부분
} Node;                 // Node 데이터형 정의 

/* 현재 노드 출력 함수 */
void printLL(Node* p){
    Node* current = p;
    while (current != NULL){
        printf("%s->", current -> data);
        current = current->link;
    }
    printf("\n");
}

void main(){

    /* 첫 번째 노드 생성 */
    Node* head;
    Node* node1 = (Node*)malloc(sizeof(Node));
    strcpy(node1->data, "다현");
    head = node1;

    /* 두 번째 노드 생성 & 첫 번째 노드의 링크로 연결 */
    Node* node2 = (Node*)malloc(sizeof(Node));
    strcpy(node2->data, "정연");
    node1->link = node2; 
    // node1은 구조체 자체가 아닌 포인터이므로 ->, 구조체 자체라면 . 

    /* 노드 추가 */
    Node* node3 = (Node*)malloc(sizeof(Node));
    strcpy(node3->data, "쯔위");
    node2->link = node3;

    Node* node4 = (Node*)malloc(sizeof(Node));
    strcpy(node4->data, "사나");
    node3->link = node4;

    Node* node5 = (Node*)malloc(sizeof(Node));
    strcpy(node5->data, "지효");
    node4->link = node5;
    node5->link = NULL;

    /* 노드 출력 */ 
    /*
        printf("%s->", head->data);
        printf("%s->", head->link->data); 
        printf("%s->", head->link->link->data);
        printf("%s->", head->link->link->link->data);
        printf("%s\n", head->link->link->link->link->data);
    */

    printLL(head);

    /* 노드 삽입 */
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, "인영");
    newNode->link = node2->link;
    node2->link = newNode;

    printLL(head);

    /* 노드 삭제 */
    node2->link = newNode->link;
    free(newNode);

    printLL(head);

    /* free */
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
}