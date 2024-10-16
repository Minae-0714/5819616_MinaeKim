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
} ThreadNode;

TreeNode* insert_node(TreeNode* root, int key);
ThreadNode* insert_thread_node(ThreadNode* root, int key);
TreeNode* GenerateBinaryTree(int inputData[], int size);
ThreadNode* GenerateThreadTree(int inputData[], int size);
void BinaryTreeInOrder(TreeNode* root);
void ThreadTreeInOrder(ThreadNode* root);
ThreadNode* create_threads(ThreadNode* root);

TreeNode* new_node(int key) {
    TreeNode* temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = malloc(sizeof(ThreadNode));
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

ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_thread_node(root, inputData[i]);
    }
    root = create_threads(root); 
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

ThreadNode* insert_thread_node(ThreadNode* root, int key) {
    if (root == NULL)
        return new_thread_node(key);
    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_thread_node(root->left, key);
    else root->right = insert_thread_node(root->right, key);

    return root;
}

ThreadNode* create_threads(ThreadNode* root) {
    static ThreadNode* prev = NULL;
    if (root != NULL) {
        create_threads(root->left);
        if (prev != NULL && prev->right == NULL) {
            prev->right = root;
            prev->rightThread = 1;  
        }
        prev = root;
        create_threads(root->right);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    while (current->left != NULL)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);
        if (current->rightThread)
            current = current->right;
        else {
            current = current->right;
            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);

    return 0;
}