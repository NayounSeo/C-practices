// 실행은 아직 안시켜봄
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 8
typedef struct _queueType* Queue;

struct _queueType {
    int queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} queueType;

void isEmpty(struct _queueType* q);
void isFull(struct _queueType* q);
void makeEmpty(struct _queueType* q);
void enqueue(struct _queueType* q, int item);
void dequeue(struct _queueType* q);

int main(void) {
    queueType* q = (queueType*)malloc(sizeof(queueType));

}

void makeEmpty(queueType* q) {
    queue = {0};
    q->front = 0;
    q->rear = 0;
    q->size = 0; 
}

void isEmpty(queueType* q) {
    if(q->front == 0 && q->front == q->rear) {
        return true;
    }
    return false;
}

void isFull(queueType* q) {
    if((q->front + 1) % MAX_QUEUE_SIZE == q->rear) {
        return true;
    }
    return false;
}

void enqueue(queueType* q, int item) {
    if(isFull(q)) {
        return;
    }
    index = (q->front + q->size) % MAX_QUEUE_SIZE;
    q->queue[index] = item;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE + 1;
    size += 1;
}

void dequeue(queueType* q) {
    if(isEmpty(q)) {
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE + 1;
    a->queue[front] = 0;
    size -= 1;
}


