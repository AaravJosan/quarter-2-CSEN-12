#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

typedef struct set{
    int count;
    int length;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
}SET;

/*  Big-O: O(1)

    The createSet function takes one argument, the maximum number of words that can be in the set. A pointer 
    *sp allocates size of SET Bytes in  memory. The function initializes count, flags and length. The function returns 
    pointer *sp.
*/

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    SET *sp = (SET*)malloc(sizeof(SET));
    assert(sp);
    
    sp->data = (void**)malloc(sizeof(void*) * maxElts);
    assert(sp->data);

    sp->flags = (char*)malloc(sizeof(char) * maxElts);
    assert(sp->flags);

    int i;
    for(i = 0; i < maxElts; i++)
        sp->flags[i] = 'E';

    sp->count = 0;
    sp->length = maxElts;
    sp->compare = compare;
    sp->hash = hash;

    return sp;
}

/*  Big-O: O(n)  

    The search function takes two arguments, a pointer pointing to the set, a pointer whos 
    element/word to be searched for and a boolean value telling us whether the element was 
    found or not. The functions gets the hash value of the element that has to be found in *sp. 
    The function checks if the index/hash is an empty or not, if its not empty, it goes to the next
    value of hash is empty. If the element is found, found changes to true and returns the index
    at which it is found. If not found, the function returns the index at which the element should be 
    added in the set.

*/

static int search(SET *sp, char *elt, bool *found) {
    int hash = (*sp->hash)(elt) % sp->length;
    int deletedIndex = -1;

    while(sp->flags[hash] != 'E' && sp->flags[hash] != 'D') {
        if(sp->flags[hash] == 'D' && deletedIndex == -1){
            deletedIndex = hash;
        }
        if((*sp->compare)(sp->data[hash], elt)) {
            *found = true;
            return hash;
        }
        hash = (hash + 1) % sp->length;
    }

    *found = false;
    return (deletedIndex != -1) ? deletedIndex : hash;
}

/*  Big-O: O(n)

    The addElement function takes in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be added to the set. The function calls the search function, which returns the index at which the 
    element is found or the index at which the word/element should be put into the set. The function is adding the element in the the 
    index and change to flag to tell us that the index is filled.
*/

void addElement(SET *sp, void *elt){
    assert(sp && elt);

    bool found;
    int index = search(sp, elt, &found);
    if(!found){
        assert(sp->count < sp->length);
        sp->count++;
        sp->data[index] = elt;
        sp->flags[index] = 'F'; 
    }
}

/*  Big-O: O(n)

    The removeElement function take in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be removed from the set. The function calls the search function, which returns the index at which the 
    element is found. The word saved in index is freed and the flag at the index is changed to deleted. The function then shifts all the elements 
    to the left, from index to count. The value of count is decreased by one.
*/

void removeElement(SET *sp, void *elt){
    assert(sp && elt);

    bool found;
    int index = search(sp, elt, &found);

    if(found){
        sp->flags[index] = 'D';
        sp->data[index] = NULL;
        sp->count--;
    }
}

/*  Big-O: O(n)

    The findElement function takes in two arguments, pointer *sp which is pointing to the initialized set and *elt which is a pointer
    pointing to the word that has to be found from the set. The search function is called, which returns the index of the word/element
    in the set changes the value of found to true. If found is true, the function returns the word, else NULL is returned. 
*/

void *findElement(SET *sp, void *elt){
    assert(sp && elt);

    bool found;
    int index = search(sp, elt, &found);
    return found? sp->data[index] : NULL;
}


/*  Big-O: O(n)

    The getElements function takes in one argument, pointer *sp which is pointing to the initialized set. A new SET *arr is initialized with
    the same size as the *sp. The elements are coppied from sp to arr. The function returns the set of words in arr.
*/

void *getElements(SET *sp){
    assert(sp);

    SET *temp = (SET*)malloc(sizeof(SET));
    assert(temp);

    temp->data = (void**)malloc(sp->length * sizeof(void*));
    assert(temp->data);

    int count = 0;
    int i;
    for(i = 0; i < sp->length; i++){
        if(sp->flags[i] == 'F'){
            temp->data[count] = sp->data[i];
            count++;
        }
    }

    return temp->data; 
}

/*  Big-O: O(n)

    THe strhash functions takes one argument, a pointer pointing to the the word whos hash
    value has to be calculated. 
*/

static unsigned strhash(char *s){
    unsigned hash = 0;
    while(*s != '\0')
        hash = 31 * hash + *s ++;
    
    return hash;
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

    The destroySet function takes in one argument, pointer *sp which is pointing to the initialized set. The function goes
    through each element/word in the set and frees it. Finally the function frees the set.
*/

void destroySet(SET *sp){
    assert(sp);
    
    int i;
    for(i = 0; i < sp->count; i++){
        free(sp->data[i]);
    }
    free(sp);
}