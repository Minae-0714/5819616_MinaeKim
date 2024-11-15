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

HeapType* create() { //힙 생성
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) { //힙 초기화
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size); //힙 크기 증가

	//크기비교
	while ((i != 1) && (item.key < h->heap[i / 2].key)){
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //힙에 삽입
}

//최소 요소 삭제
element delete_min_heap(HeapType* h) { 
	int parent, child;
	element item, temp;

	item = h->heap[1]; //최소 요소
	temp = h->heap[(h->heap_size)--]; //힙의 마지막 요소 저장, 크기 감소
	parent = 1;
	child = 2;
	while (child <= h->heap_size) { //크기 비교
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

Node* make_tree(Node* left, Node* right) { //트리 만들기
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = left;
	node->right = right;
	return node;
}

void destroy_tree(Node* root) { //트리 삭제
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(Node* root) { //리프노트인가?
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) { //배열 출력
	for (int i = 0; i < n; i++)
		printf("%d ", codes[i]);
	printf("\n");
}

void printCodes(Node* root, int codes[], int top) { //허프만 코드 출력
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

//허프만 트리 만들기
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
	int i = 0;
	Node* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create(); 
	init(heap);

	for (i = 0; i < size; i++) { //문자 힙에 삽입
		node = make_tree(NULL, NULL); //트리노드 생성
		e.ch = node->ch = characters[i]; //문자 할당
		e.key = node->weight = frequencies[i]; //가중치 할당
		e.ptree = node; 
		insert_min_heap(heap, e); //최소 힙에 삽입

		for (int j = 1; j <= heap->heap_size; j++) { 
			printf("%d ", heap->heap[j].key);
		}
		printf("\n");
	}

	//허프만 트리 구성
	for (i = 1; i < size; i++) {
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1.ptree, e2.ptree); //최소 요소들 결합
		e.key = x->weight = e1.key + e2.key; //가중치 설정
		e.ptree = x; 


		printf("///%d + %d -> %d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e); //새로운 노드 힙에 삽입

		for (int j = 1; j <= heap->heap_size; j++) {
			printf("%d ", heap->heap[j].key);
		}
		printf("\n");
	}
	e = delete_min_heap(heap); //최소 요소 삭제
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