/*  FILE: set.c
    Author: Aarav Josan
    Last Updated: 02/25/24
    Description: This C program implements a set of list, lists hat are defined in the list.h file. The set consists of the 
    number of items in the Set, the maximum length of the Set, the array of lists, a pointer to a compare function to compare
    two elements, and a pointer to a hash function that returns the hash value of the element. The user can perform various
    operations on the set such as creating the set, destroying the set, getting the number of elements in the set, adding to 
    the list, find an item in the set, and get all the items in the list as an array.
*/

#include "set.h"
#include "list.h"

#define CONSTANT 20

typedef struct node
{
	void *data;
    	struct node *next;
    	struct node *prev; 
} NODE;

typedef struct list
{
	int count; 
	struct node *head; 
    	int (*compare)(const void *data1, const void *data2);
} LIST; 

typedef struct set{
    int count;
    int length;
    LIST **data;
    int (*compare)(const void *data1, const void *data2);
    unsigned (*hash)(const void *data3);
}SET;

/*  Big-O: O(N)

    The createSet function takes three argument, the maximum number of elements that can be in the set, a pointer to the
    compare function and a pointer to the hash function. The Set is then intialized with the max length, the compare function,
    the hash function adn the array of lists.
*/

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    SET *sp = (SET*)malloc(sizeof(SET));
    assert(sp);
    
    int numlist = maxElts/CONSTANT;
    sp->length = numlist;
    sp->compare = compare;
    sp->hash = hash;

    sp->data = (LIST**)malloc(sizeof(LIST*) * numlist);
    for(int i = 0; i < numlist; i++){
        sp->data[i] = createList(compare);
    }
    assert(sp->data);

    return sp;
    
}

/*  Big-O: O(N)

    The addElement function takes in two arguments, pointer which is pointing to the  set and a pointer pointing to the element that has to be added to the set. 
    The function calls the hash function, which returns the hash at which the element is found or the index at which the word/element should be put into the set. 
    The function is adding the element to the list which is in the index given by hash.
*/

void addElement(SET *sp, void *elt) {
    assert(sp && elt);

    int hash = (*sp->hash)(elt) % sp->length;

    if (findItem(sp->data[hash], elt) == NULL) {
        addFirst(sp->data[hash], elt);
        sp->count++;
    }
}


/*  Big-O: O(N)

    The addElement function takes in two arguments, pointer which is pointing to the  set and a pointer pointing to the element that has to be removed in the set. 
    The function calls the hash function, which returns the hash at which the element is found or the index at which the word/element should be put into the set. 
    The function is rmeoving in the list that is in index hash.
*/

void removeElement(SET *sp, void *elt) {
    assert(sp && elt);

    int hash = (*sp->hash)(elt) % sp->length;


        if(findItem(sp->data[hash], elt) != NULL){
            removeItem(sp->data[hash], elt);
            sp->count--;
    }
}


/*  Big-O: O(n)

    The findElement function takes in two arguments, pointer which is pointing to the set and  a pointer pointing to the element that has to be found from the set.
    The hash function is called, which returns the index of the List where the element can be found. 
*/

void *findElement(SET *sp, void *elt) {
    assert(sp && elt);

    int hash = (*sp->hash)(elt) % sp->length;

    if (sp->data[hash] != NULL) {
        void* item = findItem(sp->data[hash], elt);
        return item;
    }

    return NULL;
}


/*  Big-O: O(N)

    The getElements function takes in one argument, pointer which is pointing to the set. A new array of void **arr is initialized with
    the same size as the *sp->count. The elements are coppied from sp to arr. The function returns the set of elements in arr.
*/

void *getElements(SET *sp){
	assert(sp);

    void **arr = malloc(sizeof(void*)*sp->count);
    int index = 0; 
    for(int i = 0; i < sp->length; i++){
        NODE *dummyNext = sp->data[i]->head->next;
        while(dummyNext != sp->data[i]->head)
        {
            arr[index] = dummyNext->data;
            index++;
            dummyNext = dummyNext->next;
        }
    }
    return arr; 
}


/*  Big-O: O(1)

    The numElements function takes in one argument, pointer which is pointing to the set. The function returns
    the value of count that is stored in the struct *sp.
*/

int numElements(SET *sp){
    assert(sp);
    return sp->count;
}

/*  Big-O: O(n)

    The destroySet function takes in one argument, pointer which is pointing to the set. The function goes
    through each element/word in the set and frees it. Finally the function frees the set.
*/

void destroySet(SET *sp){
    assert(sp);
    
    int i;
    for(i = 0; i < sp->length; i++){
        destroyList(sp->data[i]);
    }
    free(sp);
}