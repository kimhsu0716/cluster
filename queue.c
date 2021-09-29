//queue.c

#include "queue.h"
#include <stdlib.h>

void init(Queue *q){ //큐 초기화
    q->size = 0;
    q->first = q->last = NULL;
}

void push(Queue *q, elem item){
    Node *newnode = (Node *)malloc(sizeof(Node)); //새로운 노드를 동적 메모리 할당
    newnode->item = item;
    newnode->next = NULL;
    if(empty(q)) q->first = newnode;
    else q->last->next = newnode;
    q->last = newnode;
    q->size++;
}

elem pop(Queue *q){
    if(empty(q)){ //큐가 비어있으면 -1로 채워진 elem을 리턴
        elem item = {-1, -1, -1};
        return item;
    }
    Node *del = q->first;
    elem ret = del->item;
    q->first = del->next;
    q->size--;
    free(del); //삭제할 노드를 동적 메모리 해제
    return ret;
}

elem front(Queue *q){
    if(empty(q)){ //큐가 비어있으면 -1로 채워진 elem을 리턴
        elem item = {-1, -1, -1};
        return item;
    }
    return q->first->item;
}

int size(Queue *q){
    return q->size;
}

int empty(Queue *q){
    return q->size == 0;
}
