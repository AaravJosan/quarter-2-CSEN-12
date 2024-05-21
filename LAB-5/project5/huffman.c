/*  FILE: huffman.c
    AUTHOR: Aarav Josan
    LAST MODIFIED: 03/06/2024
    DESCRIPTION: This program uses the priority queue functions made in pqueue.c to implement huffman's compression
*/

#include "pqueue.h"
#include "pack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

typedef struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)(const void *data1, const void *data2);
}PQ;

/*
    returns a node with the number of time the character is seen, with its left and right parent node
*/

static struct node* mknode(int count, struct node *leftNode, struct node *rightNode){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    assert(newNode);

    newNode->count = count;
    newNode->parent = NULL;

    if(leftNode != NULL)
        leftNode->parent = newNode;
    if(rightNode != NULL)
        rightNode->parent = newNode;

    return newNode;
}

/*
    Compares two nodes, returns -1 if second node is greater, 0 if equal and 1 if first node is greater
*/

static int compare(struct node* firstNode, struct node* secondNode){
    return (firstNode->count < secondNode->count) ? -1 : (firstNode->count > secondNode->count);
}

/*
    prints the number of each letter, the bits they took up, and the product of both
*/

static void depth(struct node **arr,int counts[]){
    for(int i = 0; i < 257; i++){
        if(arr[i] != NULL){
            struct node *childNode = arr[i];
            int count = -1;
            while(childNode != NULL){
                childNode = childNode->parent;
                count++;
            }
            if(isprint((char)i) == 0)
                printf("%03o : %d x %d bits =  %d bits\n", i, counts[i], count, count * counts[i]);
            else
                printf("%c : %d x %d bits =  %d bits\n", i, counts[i], count, count * counts[i]);
        }
    }
}

/*
    Main function to do huffman compression
*/

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Eniffecient parameters\n");
        return 0;
    }
    FILE* inFilePointer;

    inFilePointer = fopen(argv[1], "r");
    assert(inFilePointer);

    int c;
    int counts[257] = {0};
    struct node *node[257] = {NULL};

    while((c = fgetc(inFilePointer)) != EOF){
        counts[c]++;
    }

    PQ *newPQ = createQueue(compare);

    for(int i = 0; i < 256; i++){
        if(counts[i] != 0){
            node[i] = mknode(counts[i], NULL, NULL);
            addEntry(newPQ, node[i]);
        }
    }

    node[256] = mknode(0 , NULL, NULL);
    addEntry(newPQ, node[256]);


    while(newPQ->count > 1){
        struct node *childOne = removeEntry(newPQ);
        struct node *childTwo = removeEntry(newPQ);
        struct node *parentNode;
        parentNode = mknode(childOne->count + childTwo->count, childOne, childTwo);   
        addEntry(newPQ, parentNode);
    }   

    depth(node, counts);
    pack(argv[1], argv[2], node); 
    
    fclose(inFilePointer);
    return 0;
}
