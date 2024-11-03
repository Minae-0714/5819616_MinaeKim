#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11 // 그래프의 최대 정점 개수
#define INF INT_MAX // 무한대

// 간선 정보
typedef struct Edge {
    int vertex;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    int n; // 정점의 개수
    Edge* adjList[MAX_VERTICES]; // 인접 리스트 배열
} GraphType;

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES * MAX_VERTICES];
    int size;
} MinHeap;

// 그래프 초기화 함수
void init_graph(GraphType* g, int vertices) {
    g->n = vertices;
    for (int i = 0; i <= vertices; i++) {
        g->adjList[i] = NULL;
    }
}

// 간선 추가 함수
void insert_edge(GraphType* g, int u, int v, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->vertex = v;
    edge->weight = weight;
    edge->next = g->adjList[u];
    g->adjList[u] = edge;

    // 무방향 그래프이므로 반대 방향 간선도 추가
    edge = (Edge*)malloc(sizeof(Edge));
    edge->vertex = u;
    edge->weight = weight;
    edge->next = g->adjList[v];
    g->adjList[v] = edge;
}

// 최소 힙 초기화 함수
void init_min_heap(MinHeap* h) {
    h->size = 0;
}

// 최소 힙 삽입 함수
void insert_min_heap(MinHeap* h, int vertex, int distance) {
    int i = h->size++;
    while (i > 0 && h->heap[(i - 1) / 2].distance > distance) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;
}

// 최소 힙에서 최소값을 추출하는 함수
HeapNode delete_min_heap(MinHeap* h) {
    HeapNode min_item = h->heap[0];
    HeapNode last_item = h->heap[--h->size];

    int parent = 0, child = 1;
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child].distance > h->heap[child + 1].distance) {
            child++;
        }
        if (last_item.distance <= h->heap[child].distance) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = last_item;
    return min_item;
}

// Distance, Found 출력
void print_status(int distance[], int visited[], int vertices) {
    printf("Distance: ");
    for (int i = 1; i <= vertices; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%d ", distance[i]);
        }
    }
    printf("\nFound: ");
    for (int i = 1; i <= vertices; i++) {
        printf("%d ", visited[i]);
    }
    printf("\n\n");
}

// Dijkstra 알고리즘
void dijkstra(GraphType* g, int start) {
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES] = { 0 };
    int order[MAX_VERTICES];
    int order_index = 0;

    for (int i = 0; i <= g->n; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    MinHeap min_heap;
    init_min_heap(&min_heap);
    insert_min_heap(&min_heap, start, 0);

    while (min_heap.size > 0) {
        HeapNode node = delete_min_heap(&min_heap);
        int u = node.vertex;

        if (visited[u]) continue;
        visited[u] = 1;
        order[order_index++] = u;

        // Distance, Found 출력
        print_status(distance, visited, g->n);

        for (Edge* edge = g->adjList[u]; edge != NULL; edge = edge->next) {
            int v = edge->vertex;
            int weight = edge->weight;

            if (!visited[v]) {
                int new_dist = distance[u] + weight;
                if (new_dist < distance[v]) {
                    distance[v] = new_dist;
                    insert_min_heap(&min_heap, v, new_dist);
                }
            }
        }
    }

    // Found Order 출력
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
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

int main() {
    GraphType g;
    init_graph(&g, MAX_VERTICES - 1);
    GenerateGraph(&g);
    dijkstra(&g, 1);
    return 0;
}
