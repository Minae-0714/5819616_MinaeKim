#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];
int visit_index = 0;       
int path[MAX_VERTICES];   
int path_index = 0;      

typedef struct {
    int n; 
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

typedef struct {
    int data[MAX_VERTICES];
    int top;
} Stack;

void init_stack(Stack* s) {
    s->top = -1;
}

int is_empty(Stack* s) {
    return (s->top == -1);
}

void push(Stack* s, int value) {
    if (s->top < MAX_VERTICES - 1) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack* s) {
    if (!is_empty(s)) {
        return s->data[(s->top)--];
    }
    return -1; 
}

void print_stack(Stack* s) {
    if (is_empty(s)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack: ");
    for (int i = s->top; i >= 0; i--) { 
        printf("%d -> ", s->data[i]);
    }
    printf("NULL\n");
}

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode* link;
}QueueNode;

typedef struct {
    QueueNode* front, * rear;
}LinkedQueueType;

void init(LinkedQueueType* q) {
    q->front = q->rear = 0;
}

int contains(Stack* s, int value) {
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i] == value) {
            return TRUE; 
        }
    }
    return FALSE; 
}

int q_is_empty(LinkedQueueType* q) {
    return(q->front == NULL);
}

int q_is_full(LinkedQueueType* q) {
    return 0;
}

void enqueue(LinkedQueueType* q, element data) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->link = NULL;
    if (q_is_empty(q)) {
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(LinkedQueueType* q) {
    QueueNode* temp = q->front;
    element data;
    if (q_is_empty(q)) {
        fprintf(stderr, "Queue is empty");
        exit(1);
    }
    else {
        data = temp->data;
        q->front = q->front->link;
        if (q->front == NULL) {
            q->rear = NULL;
        }
        free(temp);
        return data;
    }
}

GraphMatType* create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void init_mat_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if (g->n >= MAX_VERTICES) { 
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    g->n++; // 정점의 개수가 하나 늘어났다
}

void destroy_mat_graph(GraphMatType* g) {
    free(g);
}

void insert_edge_mat_graph(GraphMatType* g, int start, int end) {
    if (g->n <= start || g->n <= end) {
        fprintf(stderr, "Vertex number error\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; // 무방향 그래프라서
}

void reset_visited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0; 
    }
    visit_index = 0; 
    path_index = 0; 
}

// 그래프 생성 함수
void create_graph(GraphMatType* g) {
    // 정점 추가
    for (int i = 0; i < 11; i++) {
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

void depthFirstSearch(GraphMatType* g, int start, int target) {
    Stack s;
    init_stack(&s); 
    reset_visited(); 
    path_index = 0; 
    int visit_count = 0; 

    push(&s, start); 
    visited[start] = TRUE; 

    while (!is_empty(&s)) {
        int current = pop(&s); 
        path[path_index++] = current; 
        printf("%d ", current); 
        visit_count++; 

        if (current == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", visit_count);
            return;
        }

        for (int i = g->n - 1; i >= 0; i--) {
            if (g->adj_mat[current][i] && !visited[i]) {
                push(&s, i);
                visited[i] = TRUE;
            }
        }
    }

    printf("\n탐색 실패: %d\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
}

int breadthFirstSearch(GraphMatType* g, int start, int target) {
    LinkedQueueType q;
    init(&q);
    reset_visited(); 
    path_index = 0; 
    int visit_count = 0; 

    enqueue(&q, start); 
    visited[start] = 1; 
    path[path_index++] = start;
    visit_count++; 

    while (!q_is_empty(&q)) { 
        int current = dequeue(&q); 
        printf("%d ", current); 

        if (current == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", visit_count);
            return TRUE; 
        }

        for (int next = 0; next < g->n; next++) {
            if (g->adj_mat[current][next] && !visited[next]) { 
                enqueue(&q, next); 
                visited[next] = 1;
                path[path_index++] = next; 
                visit_count++; 
            }
        }
    }

    printf("\n탐색 실패: %d\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
    return FALSE; 
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

    GraphMatType* g;
    g = create_mat_graph();
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

            reset_visited();  
            depthFirstSearch(g, start, target);

            break;
        case 2:
            printf("시작 번호와 탐색할 값을 입력: ");
            scanf("%d %d", &start, &target);
            breadthFirstSearch(g, start, target);
            reset_visited();  

            break;
        default:
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            break;
        }
    }

    destroy_mat_graph(g); 
    return 0;
}