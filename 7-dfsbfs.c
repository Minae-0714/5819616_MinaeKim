#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11 // 최대 정점 수 

// 그래프 구조체 정의
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; 
    int numVertices; 
} GraphMatType;

// 그래프 생성
GraphMatType* create_mat_graph() {
    GraphMatType* g = (GraphMatType*)malloc(sizeof(GraphMatType));
    g->numVertices = 0;
    return g;
}

// 그래프 초기화
void init_mat_graph(GraphMatType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adjMatrix[i][j] = 0; 
        }
    }
}

// 그래프 메모리 해제 
void destroy_mat_graph(GraphMatType* g) {
    free(g); 
}

// 정점 추가 
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if (g->numVertices >= MAX_VERTICES) {
        fprintf(stderr, "Vertex limit exceeded\n"); 
        return;
    }
    g->numVertices++; 
}

// 간선 추가 
void insert_edge_mat_graph(GraphMatType* g, int start, int end) {
    if (start >= g->numVertices || end >= g->numVertices) {
        fprintf(stderr, "Invalid vertex number\n"); 
        return;
    }
    g->adjMatrix[start][end] = 1; 
    g->adjMatrix[end][start] = 1; 
}

typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;


void init_stack(Stack* s) {
    s->top = -1; 
}

bool is_empty_stack(Stack* s) {
    return s->top == -1; 
}

void push(Stack* s, int value) {
    s->items[++(s->top)] = value; 
}

int pop(Stack* s) {
    return s->items[(s->top)--]; 
}

bool is_visited[MAX_VERTICES] = { false }; // DFS 방문 체크 배열

void DFS(GraphMatType* g, int start, int target) {
    Stack s;
    init_stack(&s); 
    push(&s, start); // 시작 정점을 스택에 푸시

    int visitCount[MAX_VERTICES] = { 0 }; // 각 정점 방문 횟수 배열
    const int Limit = 2;  
    bool found = false; // 목표 정점 발견 여부
    int visited_count = 0; // 방문한 정점 수 카운트

    while (!is_empty_stack(&s)) { // 스택이 비어있지 않은 동안 반복
        int v = pop(&s); // 스택에서 정점 팝

        // 방문 횟수가 제한을 초과하지 않는 경우
        if (visitCount[v] < Limit) {
            printf("%d ", v); // 정점 방문 출력
            visitCount[v]++; // 방문 횟수 증가
            visited_count++; // 총 방문 횟수 증가

            if (v == target) { // 목표 정점을 찾은 경우
                found = true; // 목표 발견 플래그 설정
                break;  // 루프 종료
            }

            // 인접 정점들을 스택에 추가
            for (int i = g->numVertices - 1; i >= 0; i--) { // 역순으로 추가하여 나중에 정렬된 순서로 탐색
                if (g->adjMatrix[v][i] && visitCount[i] < Limit) {
                    push(&s, i); // 인접 정점이 방문 가능하면 스택에 푸시
                }
            }
        }
    }

    if (found) {
        printf("\n탐색성공 : %d\n", target);
    }
    else {
        printf("\n탐색실패 : %d\n", target);
    }
    printf("방문한 노드의 수 : %d\n", visited_count - 1);
}

typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void init_queue(Queue* q) {
    q->front = -1;
    q->rear = -1; 
}

bool is_empty_queue(Queue* q) {
    return q->front == -1; 
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) return; 
    if (q->front == -1) q->front = 0; 
    q->items[++(q->rear)] = value; 
}

int dequeue(Queue* q) {
    if (is_empty_queue(q)) return -1; 
    int value = q->items[q->front]; 
    if (q->front == q->rear) { 
        q->front = q->rear = -1; 
    }
    else {
        q->front++; 
    }
    return value; 
}

bool is_visited_bfs[MAX_VERTICES] = { false };

void BFS(GraphMatType* g, int start, int target) {
    Queue q;
    init_queue(&q);
    enqueue(&q, start); // 시작 정점을 큐에 추가
    is_visited_bfs[start] = true; // 시작 정점 방문 체크
    int visited_count = 0; // 방문한 정점 수 카운트

    while (!is_empty_queue(&q)) { // 큐가 비어있지 않은 동안 반복
        int v = dequeue(&q); // 큐에서 정점 제거
        printf("%d ", v); // 정점 방문 출력
        visited_count++; // 총 방문 횟수 증가

        if (v == target) { // 목표 정점을 찾은 경우
            printf("\n탐색 성공 : %d\n", target);
            printf("방문한 노드의 수: %d\n", visited_count - 1);
            return; // 탐색 종료
        }

        // 인접 정점 탐색
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[v][i] && !is_visited_bfs[i]) { // 인접 정점이 방문되지 않은 경우
                enqueue(&q, i); // 큐에 추가
                is_visited_bfs[i] = true; // 방문 체크
            }
        }
    }

    printf("\n탐색 실패 : %d\n", target);
    printf("방문한 노드의 수 : %d\n", visited_count - 1);
}

// 그래프 생성 함수
void create_graph(GraphMatType* g) {
    // 정점 추가
    for (int i = 0; i < MAX_VERTICES; i++) {
        insert_vertex_mat_graph(g, i);
    }
    // 간선 추가
    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);
    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 4);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 3, 4);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);
    insert_edge_mat_graph(g, 7, 10);
    insert_edge_mat_graph(g, 7, 4);
    insert_edge_mat_graph(g, 8, 10);
    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 6, 4);
    insert_edge_mat_graph(g, 7, 6);
    insert_edge_mat_graph(g, 6, 8);
    insert_edge_mat_graph(g, 8, 9);
}

int main() {
    for (int i = 0; i < 31; i++)
        printf("-");
    printf("\n");
    printf("| 1        : 깊이 우선 탐색   ㅣ\n");
    printf("| 2        : 너비 우선 탐색   ㅣ\n");
    printf("| 3        : 종료             ㅣ\n");
    for (int i = 0; i < 31; i++)
        printf("-");
    printf("\n");

    int choice;

    GraphMatType* g = create_mat_graph();
    init_mat_graph(g);

    create_graph(g);

    int start, target;

    while (1) {
        printf("\n메뉴 입력: ");
        scanf(" %d", &choice);
        if (choice == 3) {
            printf("프로그램 종료\n");
            break;
        }
        switch (choice) {
        case 1:
            printf("시작 번호와 탐색할 값을 입력: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                is_visited[i] = false; // 방문 배열 초기화
            }

            DFS(g, start, target); // DFS 호출
            break;

        case 2:
            printf("시작 번호와 탐색할 값을 입력: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                is_visited_bfs[i] = false; // 방문 배열 초기화
            }

            BFS(g, start, target);
            break;

        default:
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            break;
        }
    }

    destroy_mat_graph(g); // 메모리 해제
    return 0;
}
