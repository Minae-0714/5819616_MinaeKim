#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Node
typedef struct Node {
    int value; // 노드 값
    struct Node* left; // 왼쪽 자식
    struct Node* right; // 오른쪽 자식
    int height; // AVL 트리에서의 높이
} Node;

// 전역 변수로 선언
int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 노드의 높이 반환 
int height(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// 새로운 노드 생성
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // 새 노드의 높이 1
    return newNode;
}

// AVL 트리 RR
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // 회전 수행
    x->right = y;
    y->left = T2;

    // 높이
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// AVL 트리 LR
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // 회전 수행
    y->left = x;
    x->right = T2;

    // 높이
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 노드의 균형 인수 계산
int getBalance(Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// AVL 트리 삽입 함수
Node* insertAVL(Node* root, int value) {
    if (!root) return createNode(value); // 트리가 비어있으면 새로운 노드 반환

    if (value < root->value) 
        root->left = insertAVL(root->left, value);
    else if (value > root->value)
        root->right = insertAVL(root->right, value);
    else
        return root; // 중복값은 삽입하지 않음

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    // LL 회전
    if (balance > 1 && value < root->left->value)
        return rightRotate(root);

    // RR 회전
    if (balance < -1 && value > root->right->value)
        return leftRotate(root);

    // LR 회전
    if (balance > 1 && value > root->left->value) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL 회전
    if (balance < -1 && value < root->right->value) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// AVL 트리 삭제 함수
Node* deleteAVL(Node* root, int value) {
    if (!root) return root; 

    if (value < root->value)
        root->left = deleteAVL(root->left, value);
    else if (value > root->value)
        root->right = deleteAVL(root->right, value);
    else {
        // 노드가 하나 또는 없는 경우
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root); // 메모리 해제
            return temp;
        }
        // 오른쪽 서브트리의 최소값으로 대체
        Node* temp = root->right;
        while (temp->left) temp = temp->left;
        root->value = temp->value;
        root->right = deleteAVL(root->right, temp->value);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    // 불균형일 때
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// AVL 탐색 함수
Node* searchAVL(Node* root, int value) {
    while (root) {
        if (value == root->value) {
            compareCount++;
            return root;
        }
        else if (value < root->value) {
            root = root->left; // 왼쪽 탐색
            compareCount++;
        }
        else {
            root = root->right; // 오른쪽 탐색
            compareCount++;
        }
    }
    return NULL; // 값이 없음
}

// BST 삽입 함수
Node* insertBST(Node* root, int value) {
    if (!root) return createNode(value); // 트리가 비어있으면 새로운 노드 반환

    if (value < root->value)
        root->left = insertBST(root->left, value);
    else if (value > root->value)
        root->right = insertBST(root->right, value);

    return root; 
}
// BST 삭제 함수
Node* deleteBST(Node* root, int value) {
    if (!root) return root;

    if (value < root->value)
        root->left = deleteBST(root->left, value);
    else if (value > root->value)
        root->right = deleteBST(root->right, value);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root); // 메모리 해제
            return temp;
        }

        Node* temp = root->right;
        while (temp->left) temp = temp->left;
        root->value = temp->value;
        root->right = deleteBST(root->right, temp->value);
    }
    return root;
}

// BST 탐색 함수
Node* searchBST(Node* root, int value) {
    while (root) {
        if (value == root->value) {
            compareCount++;
            return root; // 값 찾음
        }
        else if (value < root->value) {
            compareCount++;
            root = root->left; // 왼쪽 탐색
        }
        else {
            compareCount++;
            root = root->right; // 오른쪽 탐색
        }
    }
    return NULL; // 값이 없음
}

// 트리 메모리 해제 함수
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// AVL Batch
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;      // 0~2 중 랜덤 선택
        int B = rand() % 1000;   // 0~999 중 랜덤 선택
        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            root = deleteAVL(root, B);
        }
        else if (A == 2) {
            searchCount++;
            searchAVL(root, B);
        }
    }
}

// BST Batch
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;      // 0~2 중 랜덤 선택
        int B = rand() % 1000;   // 0~999 중 랜덤 선택
        if (A == 0) {
            root = insertBST(root, B);
        }
        else if (A == 1) {
            root = deleteBST(root, B);
        }
        else if (A == 2) {
            searchCount++;
            searchBST(root, B);
        }
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL 트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    // 메모리 해제
    freeTree(root);
    return 0;
}
