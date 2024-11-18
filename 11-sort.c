#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

// 랜덤 숫자 생성
void generateRandomData(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % 1000;
    }
}

// 배열 출력
void print_sort(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", randomData[i]);
    }
    printf("\n");
}

// 선택 정렬
void doSelectionSort(int original[]) {
    int list[SIZE];
    for (int i = 0; i < SIZE; i++) {
        list[i] = original[i];
    }
    int j, least, temp;
    int final_step = 0;

    printf("Selection Sort:\n");

    for (int i = 0; i < SIZE - 1; i++) {
        least = i;

        // 현재 위치 이후에서 최소값 찾기
        for (j = i + 1; j < SIZE; j++) {
            if (list[least] > list[j]) {
                least = j;
            }
        }

        // 최소값과 현재 위치 값 교환
        if (least != i) {
            SWAP(list[i], list[least], temp);
        }

        // 출력
        if ((i + 11) % 10 == 0 && (i + 11) % 20 == 0) {
            printf("Step %d: ", i + 1);
            print_sort(list);
            printf("\n");
        }

        final_step = i;

        // 정렬 완료 여부 확인
        int isSortedCorrectly = 1;
        for (int i = 0; i < SIZE - 1; i++) {
            if (list[i] > list[i + 1]) {
                isSortedCorrectly = 0;
                break;
            }
        }
        if (isSortedCorrectly == 1)
            break;
    }
    // 마지막 단계 출력
    printf("Step %d: ", final_step + 1);
    print_sort(list);
}

// 삽입 정렬
void doInsertionSort(int original[]) {
    int totalComparisons = 0;
    int list[SIZE];

    // 원본 배열을 복사하여 정렬된 배열을 만듦
    int sortedArray[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sortedArray[i] = original[i];
    }

    printf("\n");
    printf("Insertion Sort:\n");

    // 20번 실행하여 각 반복에서 새로운 랜덤 배열을 정렬
    for (int run = 0; run < 20; run++) { // 20번 실행
        generateRandomData(list); // 새 랜덤 배열 생성

        int comparisons = 0;
        // 삽입 정렬 수행
        for (int i = 1; i < SIZE; i++) {
            int key = list[i];
            int j = i - 1;

            // 삽입 위치 탐색 및 이동
            while (j >= 0 && list[j] > key) {
                comparisons++;
                list[j + 1] = list[j];
                j--;
            }
            comparisons++;
            list[j + 1] = key;
        }

        totalComparisons += comparisons; // 비교 횟수 합산
    }

    // 정렬된 원본 배열을 삽입 정렬로 정렬
    int comparisons = 0;
    for (int i = 1; i < SIZE; i++) {
        int key = sortedArray[i];
        int j = i - 1;

        // 삽입 위치 탐색 및 이동
        while (j >= 0 && sortedArray[j] > key) {
            comparisons++;
            sortedArray[j + 1] = sortedArray[j];
            j--;
        }
        comparisons++;
        sortedArray[j + 1] = key;
    }

    totalComparisons += comparisons; // 비교 횟수 합산

    // 평균 비교 횟수 출력
    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Final Insertion Sort Result (Sorted Array):\n");
    print_sort(sortedArray); // 최종 정렬된 배열 출력
}

// 버블 정렬
void doBubbleSort(int original[]) {
    int totalMovements = 0;
    int list[SIZE];

    // 원본 배열을 복사하여 정렬된 배열을 만듦
    int sortedArray[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sortedArray[i] = original[i];
    }

    printf("\n");
    printf("Bubble Sort:\n");

    // 20번 실행하여 각 반복에서 새로운 랜덤 배열을 정렬
    for (int run = 0; run < 20; run++) { // 20번 실행
        generateRandomData(list); // 새 랜덤 배열 생성

        int movements = 0;
        // 버블 정렬 수행
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                // 인접한 두 값 비교 후 교환
                if (list[j] > list[j + 1]) {
                    int temp;
                    SWAP(list[j], list[j + 1], temp);
                    movements += 3; // 교환 작업을 3번 이동으로 간주
                }
            }
        }
        totalMovements += movements; // 이동 횟수 합산
    }

    // 정렬된 원본 배열을 버블 정렬로 정렬
    int movements = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            // 인접한 두 값 비교 후 교환
            if (sortedArray[j] > sortedArray[j + 1]) {
                int temp;
                SWAP(sortedArray[j], sortedArray[j + 1], temp);
                movements += 3; // 교환 작업을 3번 이동으로 간주
            }
        }
    }
    totalMovements += movements; // 이동 횟수 합산

    // 평균 이동 횟수 출력
    printf("Bubble Sort Move Average: %d\n", totalMovements / 20);
    printf("Final Bubble Sort Result (Sorted Array):\n");
    print_sort(sortedArray); // 최종 정렬된 배열 출력
}


int main() {
    srand(time(0));
    int randomData[SIZE];

    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
