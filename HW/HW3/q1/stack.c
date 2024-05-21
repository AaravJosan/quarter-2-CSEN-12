#include "stack.h"


//k+l-m*n+(o^p)*w/u/v*t+q
//*+AB-CD

int getSize(STACK *sp){
    assert(sp);
    return sp->count;
}

bool isEmpty(STACK *sp){
    assert(sp);
    return sp->count == 0;
}

char peek(STACK *sp){
    assert(sp);
    if(isEmpty(sp))
        return '\0';
    
    if(sp->head->letter == '(')
        return  ')';
    else if(sp->head->letter == ')')
        return '(';
        
    return sp->head->letter;
}

void push(STACK *sp, char *elt){
    assert(sp && elt);
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->letter = *elt;
    newNode->nextNode = NULL;
    sp->count++;

    if(sp->head == NULL){
        sp->head = newNode;
        return;
    }

    newNode->nextNode = sp->head;
    sp->head = newNode;
}

char *pop(STACK *sp){
    assert(sp);
    if(isEmpty(sp))
        return NULL;

    NODE *remove = sp->head;
    char *letter = &remove->letter;
    sp->head = sp->head->nextNode;
    sp->count--;
    free(remove);
    return letter;
}
