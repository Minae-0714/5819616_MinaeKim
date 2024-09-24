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

// �ʱ�ȭ �Լ�
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// ���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

// ���� �Լ�
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// ���� �Լ�
element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	return data;
}

typedef struct QueueNode {
	TreeNode* data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
} QueueType;

// ť �ʱ�ȭ
void init_queue(QueueType* q) {
	q->front = q->rear = NULL;
}

// ť�� ��� �ִ��� Ȯ��
int is_empty_queue(QueueType* q) {
	return (q->front == NULL);
}

// ť�� ����
void enqueue(QueueType* q, TreeNode* item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = item;
	temp->link = NULL;
	if (is_empty_queue(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}

// ť���� ����
TreeNode* dequeue(QueueType* q) {
	QueueNode* temp = q->front;
	TreeNode* data = temp->data;
	q->front = temp->link;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
	return data;
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	// direction�� 0�̸� ���� �ڽĿ� ��ġ
	if (direction == 0) {
		node->left = newNode;
	}
	// direction�� 1�̸� ������ �ڽĿ� ��ġ
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

int GetSumOfNodes(TreeNode* root) { // ����� ��
	if (root == NULL) return 0;

	int sum = 0;
	LinkedStackType s;
	init(&s);
	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);
		sum += node->data;

		if (node->right != NULL) push(&s, node->right);
		if (node->left != NULL) push(&s, node->left);
	}
	printf("Sum of nodes: %d\n", sum);
	return sum;
}

int GetNumberOfNodes(TreeNode* root) { // ��ü ��� �� ���ϱ�
	if (root == NULL) return 0;

	int count = 0;
	LinkedStackType s;
	init(&s);
	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);
		count++;

		if (node->right != NULL) push(&s, node->right);
		if (node->left != NULL) push(&s, node->left);
	}
	printf("Number of nodes: %d\n", count);
	return count;
}

int GetHeightOfTree(TreeNode* root) { //Ʈ���� ����
	if (root == NULL) return 0;

	QueueType q;
	init_queue(&q);
	enqueue(&q, root);
	int height = 0;

	while (!is_empty_queue(&q)) {
		int nodeCount = 0;
		QueueNode* p = q.front;
		while (p != NULL) {
			nodeCount++;
			p = p->link;
		}

		height++;

		while (nodeCount > 0) {
			TreeNode* node = dequeue(&q);

			if (node->left != NULL) enqueue(&q, node->left);
			if (node->right != NULL) enqueue(&q, node->right);

			nodeCount--;
		}
	}
	printf("Height of Tree: %d\n", height);
	return height;
}

int GetNumberOfLeafNodes(TreeNode* root) { // �ܸ� ��� �� ���ϱ�
	if (root == NULL) return 0;

	int count = 0;
	LinkedStackType s;
	init(&s);
	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);

		if (node->left == NULL && node->right == NULL)
			count++;

		if (node->right != NULL) push(&s, node->right);
		if (node->left != NULL) push(&s, node->left);
	}
	printf("Number of leaf nodes: %d\n", count);
	return count;
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);
}
