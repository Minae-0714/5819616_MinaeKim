#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

int totalMoves = 0;
int totalComparisons = 0;
int round = 0;
int isFirst = 0;

void generateRandomData(int randomData[]) {
	for (int i = 0; i < SIZE; i++) {
		randomData[i] = rand() % 1000;
	}
}

int partition(int list[], int left, int right) {
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
}

void printallArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void printArray(int array[], int size) {
	if (round % 10 == 0 && isFirst == 0) { // 10번에 한 번만 출력
		for (int i = 0; i < 10; i++) // 0 ~ 9값
			printf("%3d ", array[i]);
		printf("| ");
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
			printf("%3d ", array[i]);
		printf("\n\n");
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomData(array);
		if (i == 0) {
			printf("Quick Sort Run\n");
			doQuickSort(array, 0, SIZE - 1);

			printf("Result\n");
			printallArray(array);
		}
		else {
			doQuickSort(array, 0, SIZE - 1);
		}

	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoves / 20.0);

	return 0;
}