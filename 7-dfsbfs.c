#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11 // �ִ� ���� �� 

// �׷��� ����ü ����
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; 
    int numVertices; 
} GraphMatType;

// �׷��� ����
GraphMatType* create_mat_graph() {
    GraphMatType* g = (GraphMatType*)malloc(sizeof(GraphMatType));
    g->numVertices = 0;
    return g;
}

// �׷��� �ʱ�ȭ
void init_mat_graph(GraphMatType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adjMatrix[i][j] = 0; 
        }
    }
}

// �׷��� �޸� ���� 
void destroy_mat_graph(GraphMatType* g) {
    free(g); 
}

// ���� �߰� 
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if (g->numVertices >= MAX_VERTICES) {
        fprintf(stderr, "Vertex limit exceeded\n"); 
        return;
    }
    g->numVertices++; 
}

// ���� �߰� 
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

bool is_visited[MAX_VERTICES] = { false }; // DFS �湮 üũ �迭

void DFS(GraphMatType* g, int start, int target) {
    Stack s;
    init_stack(&s); 
    push(&s, start); // ���� ������ ���ÿ� Ǫ��

    int visitCount[MAX_VERTICES] = { 0 }; // �� ���� �湮 Ƚ�� �迭
    const int Limit = 2;  
    bool found = false; // ��ǥ ���� �߰� ����
    int visited_count = 0; // �湮�� ���� �� ī��Ʈ

    while (!is_empty_stack(&s)) { // ������ ������� ���� ���� �ݺ�
        int v = pop(&s); // ���ÿ��� ���� ��

        // �湮 Ƚ���� ������ �ʰ����� �ʴ� ���
        if (visitCount[v] < Limit) {
            printf("%d ", v); // ���� �湮 ���
            visitCount[v]++; // �湮 Ƚ�� ����
            visited_count++; // �� �湮 Ƚ�� ����

            if (v == target) { // ��ǥ ������ ã�� ���
                found = true; // ��ǥ �߰� �÷��� ����
                break;  // ���� ����
            }

            // ���� �������� ���ÿ� �߰�
            for (int i = g->numVertices - 1; i >= 0; i--) { // �������� �߰��Ͽ� ���߿� ���ĵ� ������ Ž��
                if (g->adjMatrix[v][i] && visitCount[i] < Limit) {
                    push(&s, i); // ���� ������ �湮 �����ϸ� ���ÿ� Ǫ��
                }
            }
        }
    }

    if (found) {
        printf("\nŽ������ : %d\n", target);
    }
    else {
        printf("\nŽ������ : %d\n", target);
    }
    printf("�湮�� ����� �� : %d\n", visited_count - 1);
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
    enqueue(&q, start); // ���� ������ ť�� �߰�
    is_visited_bfs[start] = true; // ���� ���� �湮 üũ
    int visited_count = 0; // �湮�� ���� �� ī��Ʈ

    while (!is_empty_queue(&q)) { // ť�� ������� ���� ���� �ݺ�
        int v = dequeue(&q); // ť���� ���� ����
        printf("%d ", v); // ���� �湮 ���
        visited_count++; // �� �湮 Ƚ�� ����

        if (v == target) { // ��ǥ ������ ã�� ���
            printf("\nŽ�� ���� : %d\n", target);
            printf("�湮�� ����� ��: %d\n", visited_count - 1);
            return; // Ž�� ����
        }

        // ���� ���� Ž��
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[v][i] && !is_visited_bfs[i]) { // ���� ������ �湮���� ���� ���
                enqueue(&q, i); // ť�� �߰�
                is_visited_bfs[i] = true; // �湮 üũ
            }
        }
    }

    printf("\nŽ�� ���� : %d\n", target);
    printf("�湮�� ����� �� : %d\n", visited_count - 1);
}

// �׷��� ���� �Լ�
void create_graph(GraphMatType* g) {
    // ���� �߰�
    for (int i = 0; i < MAX_VERTICES; i++) {
        insert_vertex_mat_graph(g, i);
    }
    // ���� �߰�
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
    printf("| 1        : ���� �켱 Ž��   ��\n");
    printf("| 2        : �ʺ� �켱 Ž��   ��\n");
    printf("| 3        : ����             ��\n");
    for (int i = 0; i < 31; i++)
        printf("-");
    printf("\n");

    int choice;

    GraphMatType* g = create_mat_graph();
    init_mat_graph(g);

    create_graph(g);

    int start, target;

    while (1) {
        printf("\n�޴� �Է�: ");
        scanf(" %d", &choice);
        if (choice == 3) {
            printf("���α׷� ����\n");
            break;
        }
        switch (choice) {
        case 1:
            printf("���� ��ȣ�� Ž���� ���� �Է�: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                is_visited[i] = false; // �湮 �迭 �ʱ�ȭ
            }

            DFS(g, start, target); // DFS ȣ��
            break;

        case 2:
            printf("���� ��ȣ�� Ž���� ���� �Է�: ");
            scanf("%d %d", &start, &target);

            for (int i = 0; i < MAX_VERTICES; i++) {
                is_visited_bfs[i] = false; // �湮 �迭 �ʱ�ȭ
            }

            BFS(g, start, target);
            break;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
            break;
        }
    }

    destroy_mat_graph(g); // �޸� ����
    return 0;
}
