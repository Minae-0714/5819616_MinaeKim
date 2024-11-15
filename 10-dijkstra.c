#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 11 // 그래프의 최대 정점 개수
#define INF INT_MAX // 무한

typedef struct {
    int n;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화
void init_graph(GraphType* g, int vertices) {
    g->n = vertices;
    for (int i = 0; i <= vertices; i++) {
        for (int j = 0; j <= vertices; j++) {
            if (i == j) {
                g->adjMatrix[i][j] = 0;
            }
            else {
                g->adjMatrix[i][j] = INF; // 초기값은 무한대
            }
        }
    }
}

void insert_edge(GraphType* g, int u, int v, int weight) {
    g->adjMatrix[u][v] = weight;
    g->adjMatrix[v][u] = weight;
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
    int distance[MAX_VERTICES]; // 시작 정점에서 각 정점까지의 거리
    int visited[MAX_VERTICES] = { 0 }; // 방문 여부
    int order[MAX_VERTICES]; // 방문 순서를 기록할 배열
    int order_index = 0; // 순서

    for (int i = 0; i <= g->n; i++) {
        distance[i] = INF; // 초기화
    }
    distance[start] = 0;

    for (int i = 1; i <= g->n; i++) {
        int u = -1;
        for (int j = 1; j <= g->n; j++) {
            if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                u = j; // 방문하지 않은 정점 중 최소 거리 정점 찾기
            }
        }

        if (distance[u] == INF) break; // 더 이상 방문할 정점이 없으면 종료

        visited[u] = 1; // 정점 방문 처리
        order[order_index++] = u; // 방문 순서에 정점 추가

        // Distance, Found 출력
        print_status(distance, visited, g->n);

        for (int v = 1; v <= g->n; v++) {
            if (g->adjMatrix[u][v] != INF && distance[u] + g->adjMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + g->adjMatrix[u][v]; // 최소 거리 업데이트
            }
        }
    }

    // 순서
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
    init_graph(&g, MAX_VERTICES - 1); // 그래프 초기화
    GenerateGraph(&g); // 그래프 생성
    dijkstra(&g, 1); // 1번 정점 dijkstra 알고리즘
    return 0;
}
