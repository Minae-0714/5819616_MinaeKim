#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 100

// 랜덤한 데이터를 생성하여 배열에 저장
void generateRandomData(int randomData[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        randomData[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 20개의 숫자만 출력하는 함수
void print20Array(int array[]) {
    for (int i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("...\n");
}

// 셸 정렬
void doShellSort(int original[], int gapType, int* comparisonCount, int* moveCount) {
    int array[ARRAY_SIZE];
    int temp, i, j, gap;
    int n = ARRAY_SIZE;
    int totalComparisons = 0, totalMoves = 0;

    int sortedArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArray[i] = original[i];
    }

    // 20회 반복 (19회 반복하는 이유는 1번은 아래 original 배열을 정렬하고자 함)
    for (int run = 1; run < 20; run++) {
        generateRandomData(array);

        gap = (gapType == 2) ? n / 2 : n / 3;
        while (gap > 0) {
            for (i = gap; i < n; i++) {
                temp = array[i];
                totalMoves++;
                j = i;
                while (j >= gap) {
                    totalComparisons++;  // 비교 횟수 증가
                    if (array[j - gap] > temp) {
                        array[j] = array[j - gap];  // 요소 이동
                        totalMoves++; // 요소 이동 횟수 증가
                    }
                    else {
                        break;  // 조건이 만족하지 않으면 탈출
                    }
                    j -= gap;
                }
                array[j] = temp;
                totalMoves++;
            }
            gap = (gapType == 2) ? gap / 2 : (gap > 1) ? gap / 3 : 0;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArray[i] = original[i];
    } 

    gap = (gapType == 2) ? n / 2 : n / 3;

    while (gap > 0) { //original 배열 정렬
        for (i = gap; i < n; i++) {
            temp = sortedArray[i];
            totalMoves++;
            j = i;
            while (j >= gap) {
                totalComparisons++;
                if (sortedArray[j - gap] > temp) {
                    sortedArray[j] = sortedArray[j - gap]; 
                    totalMoves++; // 이동 횟수 증가
                }
                else {
                    break;  // 조건이 만족하지 않으면 break
                }
                j -= gap;
            }
            sortedArray[j] = temp;
            totalMoves++;
        }

        printf("Sorting with gap = %d:\n", gap);
        print20Array(sortedArray);
        printf("\n");
        
        gap = (gapType == 2) ? gap / 2 : (gap > 1) ? gap / 3 : 0;
    }

    printf("Sorted shellArray (gap = %d):\n", gapType);
    printArray(sortedArray);
    printf("\n");

    *comparisonCount = totalComparisons / 20; // 20회 비교 횟수 평균
    *moveCount = totalMoves / 20; // 20회 이동 횟수 평균
}

// 삽입 정렬
void doInsertionSort(int original[], int* comparisonCount, int* moveCount) {
    int totalComparisons = 0, totalMoves = 0;
    int list[ARRAY_SIZE];
    int sortedArray[ARRAY_SIZE];

    // 원본 배열을 original에 저장
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sortedArray[i] = original[i];
    }

    // 20회 반복
    for (int run = 1; run < 20; run++) {
        generateRandomData(list);

        int comparisons = 0, moves = 0;
        for (int i = 1; i < ARRAY_SIZE; i++) {
            int key = list[i];
            int j = i - 1;
            while (j >= 0 && list[j] > key) { //조건이 참이면 현재 값 오른쪽으로 이동
                comparisons++;
                list[j + 1] = list[j];
                j--;
                moves++;
            }
            list[j + 1] = key;
            moves++;
        }
        totalComparisons += comparisons; // 전체 비교 횟수에 누적
        totalMoves += moves; // 전체 이동 횟수에 누적
    }

    int comparisons = 0, moves = 0;
    for (int i = 1; i < ARRAY_SIZE; i++) { // original 배열 정렬
        int key = sortedArray[i];
        int j = i - 1;
        while (j >= 0 && sortedArray[j] > key) {
            comparisons++;
            sortedArray[j + 1] = sortedArray[j];
            j--;
            moves++;
        }
        sortedArray[j + 1] = key;
        moves++;
    }

    totalComparisons += comparisons;
    totalMoves += moves;

    *comparisonCount = totalComparisons / 20; // 20회 비교 횟수 평균
    *moveCount = totalMoves / 20; // 20회 이동 횟수 평균

    printArray(sortedArray);
    printf("\n");
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", *comparisonCount, *moveCount);
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    srand(time(NULL));
    generateRandomData(array);

    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);

    return 0;
}