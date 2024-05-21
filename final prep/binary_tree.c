#include <stdio.h>
#include <stdlib.h>

// Define the structure for a BST node
struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder traversal of the BST
void inorderTraversal(struct TreeNode* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->value);
        inorderTraversal(root->right);
    }
}

//keeps going to the left to find the smallest value
struct TreeNode *findMin(struct TreeNode* root){
    if(root == NULL)
        return NULL;

    else if(root->left != NULL)
        findMin(root);
    
    return  root;
}

struct TreeNode *delete(struct TreeNode* root, int num){
    if(!root)
        return root;

    if(num > root->value)
        root->right = delete(root->right, num);
    else if(num < root->value)
        root->left = delete(root->left, num);

    else{
        //delete if the node has no children
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        //delete if the node only has a right child
        else if(root->left == NULL && root->right != NULL){
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        //delete if the node has only a left child or has two children
        else{
            struct TreeNode *temp = findMin(root);
            root->value = temp->value;
            root->left = delete(root->left, temp->value);
        }
    }
    return root;
}

struct TreeNode *search(struct TreeNode *root, int val){
    if(root == NULL){
        printf("The number was not found");
        return NULL;
    }

    if(root->value > val)
        root->left = search(root->left, val);
    else if(root->value < val)
        root->right = search(root->right, val);
    else {
        printf("The num %d was found", val);
        return root;
    }
    return NULL;
}

int main() {
    struct TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // printf("Inorder traversal of the BST: ");
    // inorderTraversal(root);
    search(root, 80);
    // Clean up memory (optional)
    // Implement a function to free the entire tree

    return 0;
}
