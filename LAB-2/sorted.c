/*  File: sorted.c
    Author: Aarav Josan
    Last Updated: 01/24/2024
    Description: This C program implements a sorted SET of words from a provided .txt file(s) from the user. The user can
    perform operations such as adding elements to the set, removing elements from the set, finding elements from the set, and
    gettig all the elements from the set.  
*/

#include "set.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct set{
    char **ptr;
    int count;
    int length;
}SET;

/*  Big-O: O(log(n))

    The search function takes three arguments, a pointer pointing to the set, a pointer pointing to the element/word 
    to be searched for, and a pointer pointing to a boolean value telling us whether the the element was found or not. 
    The function uses Binary Search to search for the element *elt in SET *sp. If the element is found, the boolean value
    turns true and the function returns the index. If the element is not found, the boolean value turns false and the function
    returns the index of where the element should be placed in the Set.
*/

static int search(SET *sp, char *elt, bool *found){
    int low = 0;
    int high = sp->count - 1;
    
    while(low <= high){
        int mid = (low + high) / 2;
        int cmp = strcmp(elt, sp->ptr[mid]);

        if(cmp == 0){
            *found = true;
            return mid;  
        }
        else if(cmp < 0){
            high = mid - 1;  
        }
        else{
            low = mid + 1; 
        }
    }

    *found = false;
    return low; 
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

    The addElement function takes in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be added to the set. The function calls the search function, which returns the index at which the 
    element is found or the index at which the word/element should be put into the set. The search function turns bool found to false if
    element is not found. The function then shifts all the elements to the right from index to count and adds the word to the set in the
    index position. The value of count is increased by one.
*/
void addElement(SET *sp, char *elt){
    assert(sp);
    assert(sp->count < sp->length);
    assert(elt);
    bool found;
    int index = search(sp, elt, &found);

    if (!found) {
        int i;
        for (i = sp->count; i > index; i--)
            sp->ptr[i] = sp->ptr[i - 1];

        sp->ptr[index] = strdup(elt);
        sp->count++;
    }
}

/*  Big-O: O(n)

    The removeElement function take in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be removed from the set. The function calls the search function, which returns the index at which the 
    element is found. The word saved in index is free. The function then shifts all the elements to the left, from index to count. The value
    of count is decreased by one.
*/

void removeElement(SET *sp, char *elt){
    assert(sp);
    assert(elt);
    bool inlist;
    int index = search(sp, elt, &inlist);
    if(!inlist)
        return;
    
    free(sp->ptr[index]);
    int i;
    for(i = index; i < sp->count - 1; i++){
        sp->ptr[i] = sp->ptr[i + 1];
    }
    sp->count--;
}

/*  Big-O: O(log n)

    The findElement function takes in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be found from the set. The search function is called, which returns the index of the word/element
    in the set changes the value of found to true. If found is true, the function returns the word, else NULL is returned. 
*/

char *findElement(SET *sp, char *elt){
    assert(sp);
    assert(elt);
    bool found;
    int index = search(sp, elt, &found);
    return found ? sp->ptr[index] : NULL;
}

/*  Big-O: O(n)

    The getElements function takes in one argument, pointer *sp which is pointing to the initialized set. A new SET *arr is initialized with
    the same size as the *sp. The elements are coppied from sp to arr. The function returns the set of words in arr.
*/

char **getElements(SET *sp){
    assert(sp);
    SET *arr = (SET*)malloc(sizeof(SET));
    assert(arr);

    arr->ptr = (char**)malloc(sp->length * sizeof(char*));
    assert(arr->ptr);

    int i;
    for(i = 0; i < sp->count; i++){
        arr->ptr[i] = strdup(sp->ptr[i]);
    }

    arr->count = sp->count;  
    arr->length = sp->length;  

    return arr->ptr;
}
