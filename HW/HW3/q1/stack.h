#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node{
    char* letter;
    struct node* nextNode;
}NODE;


typedef struct stack{
    struct node* head;
    int count;
}STACK;

int getSize(STACK*);
bool isEmpty(STACK*);
char peek(STACK*);
void push(STACK*, char*);
char *pop(STACK*);