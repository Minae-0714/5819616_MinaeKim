#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100  // 최대 정점 수
#define INF 100           // 무한 값

int parent[MAX_VERTICES]; // 부모 노드 배열

// 초기화
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) 
		curr = parent[curr];
	return curr; 
}

// Union-Find 알고리즘에서 사용되는 union 함수
void set_union(int a, int b) {
	int root1 = set_find(a);  
	int root2 = set_find(b);  
	if (root1 != root2)  // 두 정점의 루트가 다르면 union
		parent[root1] = root2; 
}

// 간선 구조체
struct Edge {
	int start, end, weight;
};

// 그래프 구조체
typedef struct GraphType {
	int n;  
	struct Edge edges[2 * MAX_VERTICES]; 
}GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
	g->n = 0; 
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 간선 추가
void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;     
	g->edges[g->n].weight = w;   
	g->n++; 
}

// 비교 함수
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return(x->weight - y->weight);  // 가중치 차
}

void QuickKruskal(GraphType* g) {
	int edge_accepted = 0;  
	int uset, vset; 
	struct Edge e;  

	set_init(g->n);  
	qsort(g->edges, g->n, sizeof(struct Edge), compare);  // 배열 정렬

	printf("Kruskal Based Kruskal\n");
	int i = 0; // 간선 인덱스

	// 선택된 간선 수가 (간선 수 - 1)보다 작고, 간선 인덱스가 유효한 동안 반복
	while (edge_accepted < (g->n - 1) && i < g->n) {
		e = g->edges[i];  
		uset = set_find(e.start); 
		vset = set_find(e.end);

		if (uset != vset) {  // 두 정점이 서로 다른 루트를 가질 경우
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++; 
	}
}

// swap
void swap(struct Edge* a, struct Edge* b) {
	struct Edge temp = *a;
	*a = *b;
	*b = temp;
}

// heapify 함수
void min_heapify(struct Edge heap[], int heap_size, int i) {
	int smallest = i; 
	int left = 2 * i + 1;  
	int right = 2 * i + 2; 

	// 더 작은 인덱스 찾기
	if (left < heap_size && heap[left].weight < heap[smallest].weight)
		smallest = left;

	if (right < heap_size && heap[right].weight < heap[smallest].weight)
		smallest = right;

	// 만약 가장 작은 인덱스가 현재 인덱스와 다르면 swap
	if (smallest != i) {
		swap(&heap[i], &heap[smallest]);
		min_heapify(heap, heap_size, smallest);
	}
}

// 간선 삽입
void insert_heap(struct Edge heap[], int* heap_size, struct Edge edge) {
	heap[*heap_size] = edge;  
	int i = (*heap_size)++;  
	while (i != 0 && heap[(i - 1) / 2].weight > heap[i].weight) {
		swap(&heap[i], &heap[(i - 1) / 2]); 
		i = (i - 1) / 2; 
	}
}

// 힙에서 최소 간선을 추출
struct Edge extract_min(struct Edge heap[], int* heap_size) {
	struct Edge root = heap[0];
	heap[0] = heap[--(*heap_size)];
	min_heapify(heap, *heap_size, 0);  
	return root;  
}

void MinHeapKruskal(GraphType* g) {
	int edge_accepted = 0;  
	int uset, vset;  
	struct Edge e;  

	set_init(g->n);  
	int heap_size = 0;  
	struct Edge heap[2 * MAX_VERTICES];  

	// 모든 간선을 힙에 삽입
	for (int i = 0; i < g->n; i++) {
		insert_heap(heap, &heap_size, g->edges[i]);
	}

	printf("\nKruskal Using Min-Heap\n");

	// 선택된 간선 수가 (간선 수 - 1)보다 작고, 힙에 간선이 남아 있는 동안 반복
	while (edge_accepted < (g->n - 1) && heap_size > 0) {
		e = extract_min(heap, &heap_size);  
		uset = set_find(e.start);
		vset = set_find(e.end);  

		if (uset != vset) {  // 두 정점이 서로 다른 루트를 가질 경우
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;  
			set_union(uset, vset); 
		}
	}
}

void GenerateGraph(GraphType* g) {
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 7, 2, 8);
	insert_edge(g, 7, 3, 6);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 9, 10, 10);
	insert_edge(g, 5, 9, 18);
}

// 메인 함수
int main(void) {
	GraphType* g; 
	g = (GraphType*)malloc(sizeof(GraphType)); 
	graph_init(g);  

	GenerateGraph(g); // 그래프 생성

	QuickKruskal(g); // Quick Sort 기반 Kruskal
	MinHeapKruskal(g); // Min-Heap 기반 Kruskal

	free(g);
	return 0;  
}
