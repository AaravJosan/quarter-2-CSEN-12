/*  File: unsorted.c
    Author: Aarav Josan
    Last Updated: 01/24/2024
    Description: This C program implements a unsorted SET of words from a provided .txt file(s) from the user. The user can
    perform operations such as adding elements to the set, removing elements from the set, finding elements from the set, and
    gettig all the elements from the set.  
*/

#include "set.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct set{
    char **ptr;
    int count;
    int length;
}SET;

/*  Big-O: O(n)

    The search function takes three arguments, a pointer pointing to the set, a pointer pointing to the element/word 
    to be searched for. The function uses Sequential Search to search for the element *elt in SET *sp. If the element 
    is found, the function returns the index. If the element is not found, the boolean value turns false and the function
    returns -1.
*/

static int search(SET *sp, char *elt){
    int i;
    for(i = 0; i < sp->count; i++){
        if(strcmp(elt, sp->ptr[i]) == 0){
            return i;
        }
    }
    return -1;
}

/*  Big-O: O(1)

    The createSet function takes one argument, the maximum number of words that can be in the set. A pointer *sp allocates 
    size of SET Bytes in  memory. The function initializes count and length. The function returns pointer *sp.
*/
SET *createSet(int maxElts){
    SET *sp = (SET*)malloc(sizeof(SET));
    assert(sp);

    sp->ptr = (char**)malloc(maxElts * sizeof(char*));
    assert(sp->ptr);

    sp->count = 0;
    sp->length = maxElts;

    return sp;
}

/*  Big-O: O(n)

    The destroySet function takes in one argument, pointer *sp which is pointing to the initialized set. The function goes
    through each element/word in the set and frees it. Finally the function frees the set.
*/
void destroySet(SET *sp){
    assert(sp);
    int i;
    for(i = 0; i < sp->count; i++)
        free(sp->ptr[i]);

        free(sp->ptr);
        free(sp);
}

/*  Big-O: O(1)

    The numElements function takes in one argument, pointer *sp which is pointing to the initialized set. The function returns
    the value of count that is stored in the struct *sp.
*/
int numElements(SET *sp){
    assert(sp);
    return sp->count;
}

/*  Big-O: O(n)

    The addElement take in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be added to the set. The function calls the search funtion. If the search function 
    returns -1 i.e word/element not in *sp, the function ends. Else, the function sets *elt at index=count. Count is 
    increased by one.
*/
void addElement(SET *sp, char *elt){
    assert(sp);
    assert(elt);
    if(search(sp, elt) == -1){
        sp->ptr[sp->count] = strdup(elt);
        sp->count = sp->count+1;
    }

}

/*  Big-O: O(n)

    The removeElement function take in two arguments, pointer *sp which is pointing to the initialized set and *elt which is 
    a pointer pointing to the word that has to be removed from the set. The function calls the search funtion. If the search 
    function returns -1 i.e word/element not in *sp, the function ends. Else, the function frees the word in the index returned
    by the search function. The last element of the Set replaces *elt at the index. Count decreseases by one.
*/

void removeElement(SET *sp, char *elt){
    assert(sp);
    assert(elt);
    char *last = sp->ptr[sp->count-1];
    int index = search(sp, elt);
    if(index != -1){
      free(sp->ptr[index]);
        sp->ptr[index] = last;
        sp->count--;
    }
}

/*  Big-O: O(n)

    The find Element function takes in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a 
    pointer pointing to the word that has to be found from the set. The search function is called, which returns the index of *elt.
    If search function returns -1, the function returns NULL. Else the function returns the pointer to the word *elt in *sp.
*/

char *findElement(SET *sp, char *elt){
    assert(sp);
    assert(elt);
    int index = search(sp, elt);
    if(index != -1)
        return sp->ptr[index];
    else
        return NULL;
}

/*  Big-O: O(n)

    The getElements function takes in one argument, pointer *sp which is pointing to the initialized set. A new SET *arr is 
    initialized with the same size as the *sp. The elements are coppied from sp to arr. The function returns the set of words in arr.
*/

char **getElements(SET *sp){
    assert(sp);
    SET *arr = (SET*)malloc(sizeof(SET));
    arr->ptr = (char**)malloc(sp->length * sizeof(char*));

    int i;
    for(i = 0; i < sp->count; i++){
        arr->ptr[i] = strdup(sp->ptr[i]);
    }

    arr->count = sp->count;  
    arr->length = sp->length;  

    return arr->ptr;
}
