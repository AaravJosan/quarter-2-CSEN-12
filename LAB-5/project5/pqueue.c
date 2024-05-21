/*  FILE: pqueue.c
    AUTHOR: Aarav Josan
    LAST MODIFIED: 03/06/2024
    DESCRIPTION: This program creates an array which is acts as a priority queue. The program can do various functions such as create queue, destroy queue, get
    number of items in array, add a item to the queue and remove an item from the queue. 
*/

#include "pqueue.h"
#include <stdlib.h>
#include <assert.h>

#define NUM_ELEMENTS 10

typedef struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)(const void *data1, const void *data2);
}PQ;


/*
    Big-O: O(1)

    This function doubles the size of the priority queue
*/

static void increaseSize(PQ* pq){
    pq->data = realloc(pq->data, sizeof(void*) * pq->length * 2);
    pq->length = pq->length * 2;
}

/*
    Big-O: O(1)

    Allocates memory and returns a pointer to a priority queue
*/

PQ *createQueue(int (*compare)()){
    PQ* newPQ = (PQ*)malloc(sizeof(PQ));
    assert(newPQ);

    newPQ->data = (void**)malloc(sizeof(void*) * NUM_ELEMENTS);
    assert(newPQ->data);

    newPQ->count = 0;
    newPQ->length = NUM_ELEMENTS;
    newPQ->compare = compare;

    return newPQ;
}

/*
    Big-O: O(N)

    Frees all the nodes in the priority queue
*/

void destroyQueue(PQ *pq){
    assert(pq);

    for(int i = 0; i < pq->count; i++)
        free(pq->data[i]);

    free(pq);
}

/*
    Big-O: O(1)

    returns the number of nodes in the priority queue
*/

int numEntries(PQ *pq){
    assert(pq);

    return pq->count;
}

/*
    Big-O: O(1)

    swaps the two values
*/

static void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

/*
    Big-O: O(N)

    adds an item to the queue
*/

void addEntry(PQ *pq, void *entry){
    assert(pq && entry);

    if(pq->count == pq->length)
        increaseSize(pq);

    pq->data[pq->count] = entry;
    pq->count++;

    int index = pq->count - 1;

    while(index > 0){
        int parent = (index - 1) / 2;
        if(pq->compare(pq->data[index], pq->data[parent]) < 0){
            swap(&pq->data[index], &pq->data[parent]);
            index = parent;
        }
        else
            break;
    }

}

/*
    Big-O: O(N)

    returns the first element in the queue
*/

void *removeEntry(PQ *pq){
    assert(pq && pq->count > 0);

    if(pq->count == 0){
        return NULL; 
    }

    swap(&pq->data[0], &pq->data[pq->count - 1]);

    void *min_element = pq->data[pq->count - 1];

    pq->count--;

    int index = 0;

    while(2 * index + 1 < pq->count){
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest_child = left_child;

        if(right_child < pq->count && pq->compare(pq->data[right_child], pq->data[left_child]) < 0){
            smallest_child = right_child;
        }
        if(pq->compare(pq->data[smallest_child], pq->data[index]) < 0){
            swap(&pq->data[index], &pq->data[smallest_child]);
            index = smallest_child;
        } 
        else 
            break;
    }

    return min_element;

}