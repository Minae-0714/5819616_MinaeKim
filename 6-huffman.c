#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
}Node;

typedef struct {
	Node* ptree;
	char ch;
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create() { //�� ����
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) { //�� �ʱ�ȭ
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size); //�� ũ�� ����

	//ũ���
	while ((i != 1) && (item.key < h->heap[i / 2].key)){
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //���� ����
}

//�ּ� ��� ����
element delete_min_heap(HeapType* h) { 
	int parent, child;
	element item, temp;

	item = h->heap[1]; //�ּ� ���
	temp = h->heap[(h->heap_size)--]; //���� ������ ��� ����, ũ�� ����
	parent = 1;
	child = 2;
	while (child <= h->heap_size) { //ũ�� ��
		if ((child < h->heap_size) && (h->heap[child].key) > (h->heap[child + 1].key))
			child++;
		if (temp.key < h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

Node* make_tree(Node* left, Node* right) { //Ʈ�� �����
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = left;
	node->right = right;
	return node;
}

void destroy_tree(Node* root) { //Ʈ�� ����
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(Node* root) { //������Ʈ�ΰ�?
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) { //�迭 ���
	for (int i = 0; i < n; i++)
		printf("%d ", codes[i]);
	printf("\n");
}

void printCodes(Node* root, int codes[], int top) { //������ �ڵ� ���
	if (root->left) {
		codes[top] = 1;
		printCodes(root->left, codes, top + 1);
	}
	if (root->right) {
		codes[top] = 0;
		printCodes(root->right, codes, top + 1);
	}
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

//������ Ʈ�� �����
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
	int i = 0;
	Node* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create(); 
	init(heap);

	for (i = 0; i < size; i++) { //���� ���� ����
		node = make_tree(NULL, NULL); //Ʈ����� ����
		e.ch = node->ch = characters[i]; //���� �Ҵ�
		e.key = node->weight = frequencies[i]; //����ġ �Ҵ�
		e.ptree = node; 
		insert_min_heap(heap, e); //�ּ� ���� ����

		for (int j = 1; j <= heap->heap_size; j++) { 
			printf("%d ", heap->heap[j].key);
		}
		printf("\n");
	}

	//������ Ʈ�� ����
	for (i = 1; i < size; i++) {
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1.ptree, e2.ptree); //�ּ� ��ҵ� ����
		e.key = x->weight = e1.key + e2.key; //����ġ ����
		e.ptree = x; 


		printf("///%d + %d -> %d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e); //���ο� ��� ���� ����

		for (int j = 1; j <= heap->heap_size; j++) {
			printf("%d ", heap->heap[j].key);
		}
		printf("\n");
	}
	e = delete_min_heap(heap); //�ּ� ��� ����
	printCodes(e.ptree, codes, top); 
	destroy_tree(e.ptree);
	free(heap);
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
	Node* root = buildHuffmanTree(characters, frequencies, size);
	int arr[MAX_ELEMENT], top = 0;
	printCodes(root, arr, top);
}

int main() {
	char characters[] = { 'a','e','i','o','u','s','t'};
	int frequencies[] = { 10,15,12,3,4,13,1 };
	int size = sizeof(characters) / sizeof(characters[0]);

	GenerateHuffmanCodes(characters, frequencies, size);

	return 0;
}