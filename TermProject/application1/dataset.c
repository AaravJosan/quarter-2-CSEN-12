/*  FILE: dataset.c
    AUTHOR: Aarav Josan
    LAST MODIFIED:
    DESCRIPTION: program to make a set and perform various functions on it
*/

#include "dataset.h"


/*
    Big-O: O(1)

    returns the hash value of the number
*/

int getHashValue(int number){
    return number % 1021;
}

/*
    Big-O: O(1)

    Allocates memory for the list and returns a pointer to the set
*/

LIST* createDataSet(int maxElts){
    LIST* lp = (LIST*)malloc(sizeof(LIST));
    assert(lp);

    lp->data = (NODE**)malloc(sizeof(NODE*) * maxElts);
    assert(lp->data);

    lp->count = 0;
    lp->max = maxElts;
    lp->minAge = 30;
    lp->maxAge = 18;

    return lp;
}

/*
    Big-O: O(n)

    Free's the meomory pointed to the list. 

*/

void destroyDataSet(LIST* lp){
    assert(lp);

    for(int i = 0; i < lp->count; i++)
        free(lp->data[i]);

    free(lp);
}

/*
    Big-O: O(1)

    Inserts the student details, i.e the id and age, to the list based on hte ids hash value
*/

void insertion(LIST *lp, int id, int age){
    assert(lp);

    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    assert(newNode);

    newNode->id = id;
    newNode->age = age;

    int hash = getHashValue(age) % lp->max;

    if(lp->data[hash] == NULL){
        lp->data[hash] = newNode;
        return;
    }

    newNode->next = lp->data[hash];
    lp->data[hash] = newNode;
    lp->count++;
}

/*
    Big-O: O(n)

    The function gets the hash value and deletes the ID from the list. 
*/

void deletion(LIST* lp, int id){
    for(int i = 0; i < lp->max; i++){
        NODE *current = lp->data[i];
        NODE *prev = current;
        while(current != NULL){
            if(current->id == id){
                printf("DELETING ID: %d, AGE: %d\n", current->id, current->age);
                prev->next = current->next;
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}

/*
    Big-O: O(1)

    returns the differnce between the oldest and youngest person
*/

int maxAgeGap(LIST* lp){
    return lp->maxAge - lp->minAge;
}

