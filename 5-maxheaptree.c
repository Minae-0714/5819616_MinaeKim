#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int heap_size;
} HeapType;

void Heapify(HeapType* h, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < h->heap_size && h->data[leftChild] > h->data[largest]) {
        largest = leftChild;
    }

    if (rightChild < h->heap_size && h->data[rightChild] > h->data[largest]) {
        largest = rightChild;
    }

    if (largest != index) {
        int temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;

        Heapify(h, largest);
    }
}

void BuildMaxHeap(HeapType* h) {
    for (int i = h->heap_size / 2 - 1; i >= 0; i--) {
        Heapify(h, i);
    }
}

void InsertMaxHeapTree(HeapType* root, int value) {
    if (root->heap_size >= MAX_SIZE) {
        printf("Heap is full.\n");
        return;
    }

    int i = root->heap_size++;
    root->data[i] = value;

    int moveCount = 0; 

    for (int j = 0; j < root->heap_size; j++) {
        printf("%d ", root->data[j]);
    }
    printf("\n");

    while (i != 0 && root->data[i] > root->data[(i - 1) / 2]) {
        int temp = root->data[i];
        root->data[i] = root->data[(i - 1) / 2];
        root->data[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
        moveCount++; 

        for (int j = 0; j < root->heap_size; j++) {
            printf("%d ", root->data[j]);
        }
        printf("\n");
    }

    printf("노드가 이동된 횟수: %d\n", moveCount);
}

int DeleteMaxHeapTree(HeapType* h) {
    if (h->heap_size == 0) {
        printf("Heap is empty.\n");
        return -1;
    }

    int root = h->data[0];
    h->data[0] = h->data[--h->heap_size];

    int current = 0;
    int moveCount = 0; 

    for (int i = 0; i < h->heap_size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");

    while (2 * current + 1 < h->heap_size) {
        int largerChild = 2 * current + 1;

        if (2 * current + 2 < h->heap_size && h->data[2 * current + 2] > h->data[largerChild]) {
            largerChild = 2 * current + 2;
        }

        if (h->data[current] < h->data[largerChild]) {
            int temp = h->data[current];
            h->data[current] = h->data[largerChild];
            h->data[largerChild] = temp;

            current = largerChild;
            moveCount++; 

            for (int i = 0; i < h->heap_size; i++) {
                printf("%d ", h->data[i]);
            }
            printf("\n");
        }
        else {
            break;
        }
    }

    printf("노드가 이동된 횟수: %d\n", moveCount);
    return root;
}

void LevelOrderPrint(HeapType* h) {
    int level = 0;
    int levelCount = 1;
    int index = 0;

    while (index < h->heap_size) {
        printf("[%d] ", level + 1);
        for (int i = 0; i < levelCount && index < h->heap_size; i++, index++) {
            printf("%d ", h->data[index]);
        }
        printf("\n");
        level++;
        levelCount *= 2;
    }
}

HeapType* generateMaxHeapTree(int inputData[], int size) {
    HeapType* root = (HeapType*)malloc(sizeof(HeapType));
    root->heap_size = size;

    for (int i = 0; i < size; i++) {
        root->data[i] = inputData[i];
    }

    BuildMaxHeap(root);
    return root;
}

void runUserInterface(HeapType* root) {
    for (int i = 0; i < 31; i++)
        printf("-");
    printf("\n");
    printf("| i        : 노드 추가        ㅣ\n");
    printf("| d        : 노드 삭제        ㅣ\n");
    printf("| p        : 레벨별 출력      ㅣ\n");
    printf("| c        : 종료             ㅣ\n");
    for (int i = 0; i < 31; i++)
        printf("-");
    printf("\n");

    char choice;
    int inputData = 0;

    while (1) {
        printf("\n메뉴 입력: ");
        scanf(" %c", &choice);

        if (choice == 'c') {
            printf("프로그램 종료\n");
            break;
        }
        switch (choice) {
        case 'i':
            printf("추가할 노드 값: ");
            scanf("%d", &inputData);
            InsertMaxHeapTree(root, inputData);
            break;
        case 'p':
            LevelOrderPrint(root);
            break;
        case 'd':
            DeleteMaxHeapTree(root);
            break;
        default:
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            break;
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 36, 21, 18, 75, 5, 70, 63, 13 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    HeapType* root = generateMaxHeapTree(inputData, size);

    runUserInterface(root);

    free(root);
    return 0;
}
