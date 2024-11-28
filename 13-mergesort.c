#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE];
int totalMoves = 0, totalComparisons = 0;
int round = 0, isfirst = 0;
int comparisonCount = 0;
int moveCount = 0;

// 랜덤 배열 생성
void generaterandomdata(int randomdata[]) {
    for (int i = 0; i < SIZE; i++) {
        randomdata[i] = rand() % 1000;
    }
}

// 처음 10개 값 출력
void printarray(int array[], int size) {
    for (int i = 0; i < 10; i++) // 처음 10개 값
        printf("%3d ", array[i]);
    printf("| ");
    for (int i = size / 2 - 1; i < size / 2 + 10 && i < SIZE; i++) // 중앙-1 ~ 중앙+10 출력
        printf("%3d ", array[i]);
    printf("\n");
}

// 최종 결과 출력
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right, int* comparisonCount, int* moveCount) {
    int i = left, j = mid + 1, k = left;

    // 왼쪽, 오른쪽 비교하면서 병합 및 정렬
    while (i <= mid && j <= right) {
        (*comparisonCount)++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        (*moveCount)++;
    }

    // 남은 왼쪽 배열 복사
    while (i <= mid) {
        sorted[k++] = list[i++];
        (*moveCount)++;
    }

    // 남은 오른쪽 배열 복사
    while (j <= right) {
        sorted[k++] = list[j++];
        (*moveCount)++;
    }

    // 정렬된 내용을 원래 배열로 복사
    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
        (*moveCount)++;
    }

    // 10번에 한 번씩 출력
    round++;
    if (round % 10 == 0 && isfirst == 0) {
        printarray(list, SIZE);
        printf("\n");
    }
}

// 합병 정렬 함수
void doMergeSort(int list[], int left, int right) {
    int size = right - left + 1; // 배열의 전체 크기

    for (int width = 1; width < size; width *= 2) { // 병합 크기를 1, 2, 4, ...로 증가
        for (int i = left; i + width <= right; i += 2 * width) { // 현재 크기로 병합
            int mid = i + width - 1; // 중간 지점
            int end = (i + 2 * width - 1 < right) ? i + 2 * width - 1 : right; // 오른쪽 끝 지점
            merge(list, i, mid, end, &comparisonCount, &moveCount);
        }
    }
}


int main() {
    int array[SIZE];
    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        generaterandomdata(array);

        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) { 
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE-1);

            printf("\nResult:\n");
            printArray(array, SIZE);
            isfirst++;
        }
        else {
            doMergeSort(array, 0, SIZE-1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
