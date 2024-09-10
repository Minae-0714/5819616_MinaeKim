#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	//list에 트리 순서에 맞는 수 입력
	int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
	printf("\n");
}

void ArrayPreOrder(int* tree, int index, int size) {
	if (index < size && tree[index] != -1) {
		printf("%d ", tree[index]);
		ArrayPreOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
		ArrayPreOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
	}
}

void ArrayInOrder(int* tree, int index, int size) {
	if (index < size && tree[index] != -1) {
		ArrayInOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
		printf("%d ", tree[index]);
		ArrayInOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
	}
}

void ArrayPostOrder(int* tree, int index, int size) {
	if (index < size && tree[index] != -1) {
		ArrayPostOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
		ArrayPostOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
		printf("%d ", tree[index]);
	}
}

void ArrayOrders(int* tree, int size) {
	ArrayPreOrder(tree, 0, size);
	printf("\n");
	ArrayInOrder(tree, 0, size);
	printf("\n");
	ArrayPostOrder(tree, 0, size);
	printf("\n");
}

//노드를 만들고, 입력받은 node의 direction(0:left, l:right)값에 따라
//올바른 위치에 해당 노드를 배치하는 함수
void PlaceNode(TreeNode* node, int direction, int data) {
	// 새로운 노드 생성
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;  // 새 노드의 자식 포인터 초기화
	newNode->right = NULL;

	// direction이 0이면 왼쪽 자식에 배치
	if (direction == 0) {
		node->left = newNode;
	}
	// direction이 1이면 오른쪽 자식에 배치
	else {
		node->right = newNode;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}


void LinkPreOrder(TreeNode* node) {
	if (node != NULL) {
		printf("%d ", node->data);
		LinkPreOrder(node->left);
		LinkPreOrder(node->right);
	}
}

void LinkInOrder(TreeNode* node) {
	if (node != NULL) {
		LinkInOrder(node->left);
		printf("%d ", node->data);
		LinkInOrder(node->right);
	}
}

void LinkPostOrder(TreeNode* node) {
	if (node != NULL) {
		LinkPostOrder(node->left);
		LinkPostOrder(node->right);
		printf("%d ", node->data);
	}
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
	printf("\n");
}

int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;;

	//각각의 방식(array, link)에 따른 트리 생성
	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	//각 생성한 트리를 순회
	ArrayOrders(arr, 15);
	printf("\n");
	LinkOrders(root);

	return 0;
}