#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

int totalMoveCount = 0;
int totalComparisons = 0;
int rounds = 0;
int isFirst = 0;
int comparisonCount;
int moveCount;

// 랜덤 배열 생성
void generateRandomData(int randomData[]) {
	for (int i = 0; i < SIZE; i++) {
		randomData[i] = rand() % 1000;
	}
}

// 배열 중간 값 출력
void printarray(int array[]) {
	if (rounds % 10 == 0 && isFirst == 0) {
		for (int i = 40; i < 60; i++) // 40 ~ 60 위치에 있는 값 출력
			printf("%d ", array[i]);
		printf("\n\n");
	}
    rounds++;
}

// 모든 배열 출력
void printArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

/*int partition(int list[], int left, int right) {
	int pivot = list[right]; // 피벗을 배열의 마지막 요소로 설정
	int i = left - 1; // 피벗보다 작은 요소의 마지막 인덱스

	for (int j = left; j < right; j++) {
		totalComparisons++; // 비교 횟수 증가
		if (list[j] <= pivot) { // 피벗보다 작은 경우
			i++;
			// list[i]와 list[j] 교환
			int temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			totalMoves += 3; // 교환 작업: 3번의 이동 발생
		}
	}

	// 피벗을 적절한 위치로 이동
	int temp = list[i + 1];
	list[i + 1] = list[right];
	list[right] = temp;
	totalMoves += 3; // 교환 작업: 3번의 이동 발생

	return i + 1; // 피벗의 최종 위치 반환
}

void doQuickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		doQuickSort(list, left, q - 1);
		doQuickSort(list, q + 1, right);
	}
}*/ // 재귀적인 방법

int partition(int list[], int left, int right) {
    int pivot = list[right]; // 피벗을 마지막 요소로 설정
    int i = left - 1; // 피벗보다 작은 요소의 마지막 인덱스

    for (int j = left; j < right; j++) {
        comparisonCount++; // 비교 횟수 증가
        if (list[j] <= pivot) { // 피벗보다 작은 경우
            i++;
            // list[i]와 list[j] 교환
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
            moveCount += 3; // 교환 작업: 3번의 이동 발생
        }
    }

    // 피벗을 적절한 위치로 이동
    int temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;
    moveCount += 3; // 교환 작업: 3번의 이동 발생

    printarray(list);
    return i + 1; // 피벗의 최종 위치 반환
}

// 반복적인 Quick Sort
void doQuickSort(int list[], int left, int right) {
    int stack[SIZE];
    int top = -1;

    // 초기 구간을 스택에 삽입
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        // 스택에서 구간을 꺼냅니다.
        right = stack[top--];
        left = stack[top--];

        // 분할 작업 수행
        int pivot = partition(list, left, right);
		printarray(list);

        // 피벗 기준으로 오른쪽 구간을 스택에 삽입
        if (pivot + 1 < right) {
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }

        // 피벗 기준으로 왼쪽 구간을 스택에 삽입
        if (pivot - 1 > left) {
            stack[++top] = left;
            stack[++top] = pivot - 1;
        }
    }
}

// 메인함수
int main(int argc, char *argv[]) {
	srand(time(NULL));
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomData(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Quick Sort Run\n");
			doQuickSort(array, 0, SIZE - 1);

			printf("Result\n");
			printArray(array, SIZE);
            isFirst++;
		}
		else {
			doQuickSort(array, 0, SIZE - 1);
		}
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

	return 0;
}