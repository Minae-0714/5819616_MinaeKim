#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node* right, * left;
} TreeNode;

typedef struct thread_tree_node {
    int data;
    struct thread_tree_node* right, * left;
    int rightThread;
} ThreadTree;

TreeNode* insert_node(TreeNode* root, int key);
ThreadTree* insert_thread_node(ThreadTree* root, int key);
TreeNode* GenerateBinaryTree(int inputData[], int size);
ThreadTree* GenerateThreadTree(int inputData[], int size);
void BinaryTreeInOrder(TreeNode* root);
void ThreadTreeInOrder(ThreadTree* root);

TreeNode* new_node(int key) {
    TreeNode* temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

ThreadTree* new_thread_node(int key) {
    ThreadTree* temp = malloc(sizeof(ThreadTree));
    temp->data = key;
    temp->right = temp->left = NULL;
    temp->rightThread = 0; 
    return temp;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

ThreadTree* GenerateThreadTree(int inputData[], int size) {
    ThreadTree* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_thread_node(root, inputData[i]);
    }
    return root;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);
    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_node(root->left, key);
    else root->right = insert_node(root->right, key);

    return root;
}

ThreadTree* insert_thread_node(ThreadTree* root, int key) {
    if (root == NULL)
        return new_thread_node(key);
    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_thread_node(root->left, key);
    else root->right = insert_thread_node(root->right, key);

    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

void ThreadTreeInOrder(ThreadTree* root) {
    if (root != NULL) {
        ThreadTreeInOrder(root->left);
        printf("%d ", root->data);
        ThreadTreeInOrder(root->right);
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // 배열 크기 계산

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);

    printf("\n");

    ThreadTree* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);

    return 0;
}
