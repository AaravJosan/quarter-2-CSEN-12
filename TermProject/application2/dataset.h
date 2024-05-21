
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

typedef struct node{
    int age;
    int id;
    struct node* next;
}NODE;

typedef struct list{
    NODE** data;
    int count;
    int max;
} LIST;



LIST* createDataSet(int);
void destroyDataSet(LIST*);
void searchAge(LIST*, int);
void insertion(LIST*, int, int);
void deletion(LIST*, int);
int maxAgeGap(void);
int getHashValue(int);