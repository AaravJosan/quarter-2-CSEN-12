#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct node{
    char value;
    struct node* left;
    struct node* right;
}NODE;

NODE* createNode(char value){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(NODE* root){
    if(root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

NODE* buildTree(char** expression){
    assert(expression);

    char val = **expression;
    (*expression)++;

    if (isdigit(val) || isalpha(val)){
        return createNode(val);
    }

    NODE* node = createNode(val);

    node->left = buildTree(expression);
    node->right = buildTree(expression);

    return node;
}

void inorderTraversal(NODE* root){
    if(root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%c ", root->value);
    inorderTraversal(root->right);
}

int main(){
    char expression[] = "*+AB-CD"; //write prefix expression here 
    char* exprPtr = expression;

    NODE* root = buildTree(&exprPtr);

    inorderTraversal(root);
    printf("\n");

    freeTree(root);
}
