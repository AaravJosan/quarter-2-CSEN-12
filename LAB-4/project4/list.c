/*  FILE: list.c
    Author: Aarav Josan
    Last Updated: 02/25/24
    Description:  This C progran implements a  circular list, where each element is a in the list is a Node. The Node consists of data it is storing and
    two pointers. One to the next Node in the list and one to the previous Node in the List. The List consists of the head Node, the count (number of nodes 
    in the list), and a pointer to the function compare which is used to compare data. The user can perform operations on the list such as, creating a list,
    destroying/freeing the elements to the list, get the number of elements in the list, add an elements to the start of the list, add an element to the end of
    the list, remove the first element of the list, remove the last element of the list, return the first element, return the last element, find an element in the 
    list, remove item in list, and get all the elements in the list. 
*/

#include "list.h"

typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list{
    int count;
    struct node *head;
    int (*compare)(const void *data1, const void *data2);
}LIST;

/*  Big-O: O(1)

    The createList function takes in one argument, a pointer to the function compare. A pointer lp is created which points to the list. The head Node of the list
    is a dummy Node which doesnt hold any data. Therefore its next and previous node point to itself when its initialized. Set the count of the list to 0 and pass
    the compare function. 
*/

LIST *createList(int (*compare)()){
    LIST* lp = (LIST*)malloc(sizeof(LIST));
    assert(lp);

    NODE* dummy = (NODE*)malloc(sizeof(NODE));
    dummy->data = NULL;
    dummy->next = dummy;
    dummy->prev = dummy;

    lp->head = dummy;
    lp->count = 0;
    lp->compare = compare;

    return lp;
}

/*  Big-O: O(N)

    The destoySet function take in one argument, a pointer to the list. The function goest hrough each Node in the List and frees it. Finally the function 
    frees the List.
*/

void destroyList(LIST* lp){
    assert(lp);

    NODE* temp = lp->head->next;
    NODE* dummy = lp->head;

    while(temp !=  dummy){
        NODE* rem = temp;
        temp = temp->next;
        free(rem);
    }

    free(lp);
}

/*  Big-O: O(1)

    The numElements function takes in one argument, pointer to the list. The function returns the value of count that is stored in the struct *lp.
*/

int numItems(LIST *lp){
    assert(lp);

    return lp->count;
}

/* Big-O: O(1)

    The addFirst function takes in two arguments, a pointer to the list and a pointer to the item that has to be added to the list. If the dummy is the only Node 
    present in the List, then the dummys prev and next point to the new Node. Same happens to the new Node that is added. Else, the new Node's next points to the 
    where dummy's next points, and dummy's next pointer now changes to point to the new Node. The new Node's previous points the the dummy. and the orignal first
    Node (now the second Node), previous is set to the new Node.  
*/

void addFirst(LIST *lp, void *item){
    assert(lp && item);

    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = item;

    NODE* dummy = lp->head;
    NODE* firstNode = dummy->next;

    if(firstNode == NULL){
        dummy->next = newNode;
        dummy->prev = newNode;
        newNode->next = dummy;
        newNode->prev = dummy;
    }
    else{
        newNode->next = dummy->next;
        firstNode->prev = newNode;
        dummy->next = newNode;
        newNode->prev = dummy;
    }

    lp->count++;
}

/* Big-O: O(1)

    The addLast function takes in two arguments, a pointer to the list and a pointer to the item that has to be added to the list. If the dummy is the only Node 
    present in the List, then the dummys prev and next point to the new Node. Same happens to the new Node that is added. Else, the new Node's next points to the 
    dummy node, and dummy's prev pointer now changes to point to the new Node. The new Node's previous points the the dummy's previous and the orignal last
    Node (now the second last Node), next is set to the new Node.  
*/

void addLast(LIST *lp, void *item){
    assert(lp && item);

    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = item;

    NODE* dummy = lp->head;
    NODE* lastNode = dummy->prev;

    if(lastNode == NULL){
        dummy->next = newNode;
        dummy->prev = newNode;
        newNode->next = dummy;
        newNode->prev = dummy;
    }
    else{
        newNode->next = dummy;
        newNode->prev = dummy->prev;
        dummy->prev = newNode;
        lastNode->next = newNode;
    }

    lp->count++;
}

/* Big-O: O(1)

    The removeFirst function takes in one argument, a pointer to the list. The function removes the Node pointed to by dummy->next. 
*/


void *removeFirst(LIST* lp){
    assert(lp);

    if(lp->count == 0)
        return NULL;

    lp->count--;

    NODE* dummy = lp->head;
    NODE* first = dummy->next;

    dummy->next = first->next;
    first->next->prev = dummy;

    
    NODE* temp = first;

    return temp->data;
}

/*  Big-O: O(1)

    The removeLast function takes in one argument, a pointer to the list. The function removes the Node pointed to by dummy->last. 
*/

void *removeLast(LIST *lp){
    assert(lp);

    if(lp->count == 0)
        return NULL;

    lp->count--;

    NODE* dummy = lp->head;
    NODE* last = dummy->prev;

    dummy->prev = last->prev;
    last->prev->next = dummy;


    NODE* temp = last;
    free(last);
    return temp->data;
}

/*  Big-O: O(1)

    The getFirst function takes in one argument, a pointer to the list. The function returns the data in the node pointed to by dummy->next. 
*/

void *getFirst(LIST *lp){
    assert(lp);

    return lp->head->next->data;
}

/*  Big-O: O(1)

    The getLast function takes in one argument, a pointer to the list. The function returns the data in the node pointed to by dummy->last. 
*/

void *getLast(LIST *lp){
    assert(lp);

    return lp->head->prev->data;
}


/*  Big-O: O(N)

    The removeItem function takes in two argument, a pointer to the list and a pointer item that has to be removed. The function goes through the list and removes 
    the Node that is holding the item that has to be removed.  
*/

void removeItem(LIST *lp, void *item){
    assert(lp && item);

    NODE* dummy = lp->head;
    NODE* temp = dummy;

    for(int i = 0; i < lp->count; i++){
        if(temp->data == NULL) temp = temp->next;
        if((*lp->compare)(item, temp->data) == 0){
            NODE* deleteNode = temp;
            temp->prev->next = deleteNode->next;
            temp->next->prev = deleteNode->prev;
            free(deleteNode);
            lp->count--;
            return;
        }
        
        temp = temp->next;
    }
}

/*  Big-O: O(N)

    The findItem function takes in two argument, a pointer to the list and a pointer item that has to be found. The function goes through the list and looks
    for the Node that is holding the item.  
*/

void *findItem(LIST *lp, void *item){
    assert(lp && item);

    NODE* dummy = lp->head;
    NODE* temp = dummy->next;

    for(int i = 0; i < lp->count; i++){
        if((*lp->compare)(item, temp->data) == 0)
            return temp->data;
        
        temp = temp->next;
    }

    return NULL;
}

/*  Big-O: O(N)

    The getItems function takes in one argument, a pointer to the list. The function creates a new array and adds all the data in the list to the array and 
    returns the array.
*/

void *getItems(LIST *lp){
    assert(lp);
    
    void** arr = (void**)malloc(lp->count * sizeof(void*));

    assert(arr);

    NODE* first = lp->head->next;
   
   int i = 0;
    while(first != lp->head){
        arr[i] = first;
        first = first->next;
        i++;
    }

    return arr;
}
