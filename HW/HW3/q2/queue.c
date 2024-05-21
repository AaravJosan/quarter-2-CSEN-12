#include "queue.h"


NODE* newNode(int data) {
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    assert(temp);

    temp->data = data;
    temp->nextNode = NULL;
    return temp;
}

bool isEmpty(struct queue *qp){
    return qp->size == 0;
}

bool isFull(struct queue *qp){
    return qp->size == qp->max;
}

void enqueue(struct queue *qp, int item){
    if(isFull(qp))
        return;
    
    NODE* new = newNode(item);
    qp->size++;

    if(isEmpty(qp)){
        qp->front = new;
        qp->rear = qp->front;
        return;
    }

    NODE* temp = qp->front;
    while(temp->nextNode != NULL)
        temp = temp->nextNode;
    
    temp->nextNode = new;
    return;
}

NODE* dequeue(struct queue* qp){
    if(isEmpty(qp))
        return NULL;
    
    NODE* temp = qp->front;
    qp->front = qp->front->nextNode;

    return temp;
}

