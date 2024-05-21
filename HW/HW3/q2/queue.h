#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

typedef struct node {
    int data;
    struct node* nextNode;
} NODE;

struct queue{
    NODE* front, * rear;
    int size;
    int max;
};

NODE* newNode(int);
struct queue* createQueue(int);
void enqueue(struct queue*, int);
bool isEmpty(struct queue*);
bool isFull(struct queue*);