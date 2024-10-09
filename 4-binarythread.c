#include <stdio.h>
#include <stdlib.h>

// �Ϲ� ����Ʈ�� ��� ����ü
typedef struct tree_node {
    int data;
    struct tree_node* right, * left;
} TreeNode;

// ������ ����Ʈ�� ��� ����ü
typedef struct thread_tree_node {
    int data;
    struct thread_tree_node* right, * left;
    int rightThread;  // ������ ���θ� ǥ�� (1: ������, 0: �ڽ� ���)
} ThreadTree;

TreeNode* insert_node(TreeNode* root, int key);
ThreadTree* insert_thread_node(ThreadTree* root, int key);
TreeNode* GenerateBinaryTree(int inputData[], int size);
ThreadTree* GenerateThreadTree(int inputData[], int size);
void BinaryTreeInOrder(TreeNode* root);
void ThreadTreeInOrder(ThreadTree* root);
ThreadTree* create_threads(ThreadTree* root);

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

// �Ϲ� ����Ʈ�� ����
TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

// ������ ����Ʈ�� ����
ThreadTree* GenerateThreadTree(int inputData[], int size) {
    ThreadTree* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_thread_node(root, inputData[i]);
    }
    root = create_threads(root); // ������ ���� ����
    return root;
}

// ����Ʈ�� ��� ����
TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);
    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_node(root->left, key);
    else root->right = insert_node(root->right, key);

    return root;
}

// ������ ����Ʈ�� ��� ����
ThreadTree* insert_thread_node(ThreadTree* root, int key) {
    if (root == NULL)
        return new_thread_node(key);
    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_thread_node(root->left, key);
    else root->right = insert_thread_node(root->right, key);

    return root;
}

// ���� ��ȸ�� ���� ������ ���� ����
ThreadTree* create_threads(ThreadTree* root) {
    static ThreadTree* prev = NULL;
    if (root != NULL) {
        create_threads(root->left);
        if (prev != NULL && prev->right == NULL) {
            prev->right = root;
            prev->rightThread = 1;  // ������ ǥ��
        }
        prev = root;
        create_threads(root->right);
    }
    return root;
}

// ���� ��ȸ(���) - �Ϲ� ����Ʈ��
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// ���� ��ȸ(�ݺ�) - ������ ����Ʈ��
void ThreadTreeInOrder(ThreadTree* root) {
    ThreadTree* current = root;

    // ���� ���� ���� �̵�
    while (current->left != NULL)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);

        // �����尡 ������ ������ ���� �̵�
        if (current->rightThread)
            current = current->right;
        else {
            // ������ ����Ʈ���� ���� ���� ���� �̵�
            current = current->right;
            while (current != NULL && current->left != NULL)
                current = current->left;
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // �Ϲ� ����Ž�� Ʈ�� ����
    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // ������ ����Ʈ�� ����
    ThreadTree* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder (iterative): ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);

    return 0;
}