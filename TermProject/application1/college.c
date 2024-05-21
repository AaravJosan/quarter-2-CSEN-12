/*  FILE: dataset.c
    AUTHOR: Aarav Josan
    LAST MODIFIED:
    DESCRIPTION:  driver program that makes the college dataset
*/


#include "dataset.h"

#define MAX_ELEMENTS 3000

/*  
    Big-O: O(1)

    Generate a random number between 1 and 2
*/

static int randomID(void){
    return (rand() % 2) + 1;
}

/*
    Big-O: O(1)

    Generate a random number between 18 and  30
*/

static int randomAge(void){
    return rand() % (30 + 1 - 18) + 18;
}


/*
    Big-O: O(n)

    The search function finds the hash value of the Age. It then looks at the linked list that is found in that index of the array of NODES. If found, the function
    prints the ID and age. 
*/

static void search(LIST *lp, int age){
    int hash = getHashValue(age);

    NODE *current = lp->data[hash];

    while(current != NULL){
        printf("ID: %d, Age: %d\n", current->id, current->age);
        current = current->next;
    }
}

/*
    Big-O: O(n)

    Main function. Creates 1000 students and then searches for student with an ID of 512 and deletes that student details from the LIST
*/

int main(void) {
    time_t t;
    srand((unsigned int)time(&t));

    LIST* lp = createDataSet(MAX_ELEMENTS);

    int prevID = 0;
    for (int i = 0; i < 1000; i++) {
        int newID = randomID() + prevID;
        int newAge = randomAge();
        if(newAge > lp->maxAge)
            lp->maxAge = newAge;
        else if(newAge < lp->minAge)
            lp->minAge = newAge;
            
        insertion(lp, newID, newAge);
        prevID = newID;
    }

    search(lp, 25);
    printf("%d\n", maxAgeGap(lp));
    deletion(lp, 1);

    destroyDataSet(lp);
    return 0;
}