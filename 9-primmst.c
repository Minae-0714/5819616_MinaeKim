#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 100L

// 그래프 구조체
typedef struct GraphType {
	int n;
	int weight [MAX_VERTICES][MAX_VERTICES];
}GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) {
	g->n = 0; // 정점 개수 초기화
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->weight[i][j] = INF; // 간선 가중치 무한대
		}
	}
}

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 거리 정점 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		v = i;
		break;
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))v = i;
	}
	return(v);
}

// 간선 추가
void insert_edge(GraphType* g, int u, int v, int w) {
	if (u >= MAX_VERTICES || v >= MAX_VERTICES) {
		printf("정점 번호가 너무 큽니다.\n");
		return;
	}
	g->weight[u][v] = w; 
	g->weight[v][u] = w;
	if (u >= g->n) g->n = u + 1;
	if (v >= g->n) g->n = v + 1;
}

// prim 알고리즘
void FindPrimMST(GraphType* g) {
	int i, u, v;

	// 배열 초기화
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		selected[u] = FALSE;
	}

	// 시작 정점의 거리 0
	distance[1] = 0;
	printf("Prim MST Algorithm\n");

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // 최소 거리 정점 선택
		selected[u] = TRUE;      

		if (distance[u] == INF) return; // 연결된 간선이 없으면 종료

		printf("정점 %d 추가\n", u);

		// 선택된 정점과 연결된 모든 정점의 거리 갱신
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
				distance[v] = g->weight[u][v];
			}
		}
	}
}

// 그래프 생성
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

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);

	FindPrimMST(g);

	free(g);
	return 0;
}