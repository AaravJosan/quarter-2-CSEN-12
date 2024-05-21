#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    char val;
    struct treeNode *right, *left;
}NODE;

int isOperator(char val){
    if(val == '+' || val == '-' || val == '*' || val == '/' || val == '^')
        return 1;
    else
        return 0;
}

NODE *createNode(char val){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

NODE *insert(NODE* root, char val){
    if(root == NULL)
        return createNode(val);

    if(isOperator(val)){
        root = createNode(val);
        root->right = insert(root->right, val);
        root->left = insert(root->left, val);
    }
    else {
        return createNode(val);
    }
    return root;
}
