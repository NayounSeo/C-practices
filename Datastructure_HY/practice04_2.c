#include <stdio.h>
#include <stdlib.h>
/* 사실 수정해야 함 ㅎㅅㅎ TODO*/
typedef enum { false, true } bool;

typedef struct {
    int item;
    struct QueueNode* link;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} QueueType;

bool makeEmpty(QueueType* q);
bool enqueue(QueueType* q, int item);
bool dequeue(QueueType *q);
bool isEmpty(QueueType* q);

int main(void) {
    QueueType* q = (QueueType*)malloc(sizeof(QueueType));
    makeEmpty(q);

    return 0;
}

bool makeEmpty(QueueType* q) {
    q->front = NULL;
    q->rear = NULL;
    return true;
}

bool enqueue(QueueType* q, int item) {
    QueueNode* newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->link = NULL;

    //큐에 아이템이 있을 때
    if (q->front != NULL) {
        (q->rear)->link = newNode;
        q->rear = newNode;
        printf("아이템이 있었어. %d\n", item);
        return true;
    }
    // 큐가 초기 상태일 때
    q->front = newNode;
    q->rear = newNode;
    printf("아이템이 없었어\n");

    return true;
}

bool dequeue(QueueType* q) {
    if(isEmpty(q) == 0) {
        return false;
    }
    QueueNode* tempNode = q->front;
    q->front = (q->front)->link;
    printf("팝!\n");
    free(tempNode);

    //뭔가 rear에 조건이 더 들어가야 하나..
    if (isEmpty(q) == 0) {
        return false;
    }
    return true;
}

bool isEmpty(QueueType* q) {
    if (q->front == NULL && q->rear == NULL) {
        return true;
    }
    return false;
}

