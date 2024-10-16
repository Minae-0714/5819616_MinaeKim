#include <stdio.h>

#define MAX_SIZE 100

void swap(int* a, int* b) { 
    int temp = *a;
    *a = *b;
    *b = temp;
}

//�� ����
void heapify(int inputData[], int n, int i) {
    int largest = i; //���� ū ������ ����
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    //ũ���
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    //ū ���� ��Ʈ�� �ƴ϶�� swap �ڽ�Ʈ�� heapify
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        heapify(inputData, n, largest);
    }
}

//�迭->��
void BuildMaxHeap(int inputData[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(inputData, n, i);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n) {

    for (int i = 1; i <= n; i++) {
        BuildMaxHeap(inputData, i);
        //�� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  //��Ʈ ������ �� swap
        heapify(inputData, i, 0);  //��Ʈ ���� �� ����
        //�� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
