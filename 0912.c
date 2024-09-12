#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

// 초기화 함수
void init(LinkedStackType* s)
{
	s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
// 포화 상태 검출 함수
int is_full(LinkedStackType* s)
{
	return 0;
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
	printf("push(%d) ", item->data);
}

element pop(LinkedStackType* s) {
	if (is_empty(s)) {
		printf("스택이 비어있습니다.\n");
		return NULL;
	}
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	printf("pop(%d) ", data->data);
	return data;
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL; 
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

void LinkPreOrder(TreeNode* root, LinkedStackType* s) {
	TreeNode* current = root;

	while (current != NULL || !is_empty(s)) {
		while (current != NULL) {
			push(s, current);
			printf("visit(%d)\n", current->data);
			current = current->left;
		}

		current = pop(s);
		current = current->right;
	}
}

void LinkInOrder(TreeNode* node, LinkedStackType* s) {
	TreeNode* current = node;

	while (current != NULL || !is_empty(s)) {
		while (current != NULL) {

			push(s, current);
			current = current->left;
		}
		current = pop(s);
		printf("visit(%d)\n", current->data);

		current = current->right;
	}
}

void LinkPostOrder(TreeNode* root, LinkedStackType* s) {
	TreeNode* current = root;
	TreeNode* lastVisited = NULL;

	while (current != NULL || !is_empty(s)) {
		while (current != NULL) {
			push(s, current);
			current = current->left;
		}

		TreeNode* peekNode = s->top->data;

		if (peekNode->right != NULL && lastVisited != peekNode->right) {
			current = peekNode->right;
		}
		else {
			current = pop(s);
			printf("visit(%d)\n", current->data);
			lastVisited = current;
			current = NULL;
		}
	}
}

void LinkOrders(TreeNode* root) {
	LinkedStackType stack;
	init(&stack);

	printf("\nPreOrder 순회:\n");
	LinkPreOrder(root, &stack);

	printf("\n\nInOrder 순회:\n");
	LinkInOrder(root, &stack);

	printf("\n\nPostOrder 순회:\n");
	LinkPostOrder(root, &stack);
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	LinkOrders(root);

	return 0;
}