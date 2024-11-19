//#include <stdio.h>
//#include <stdlib.h>
//#define SIZE 100
//
//int sorted[SIZE];
//int totalMoves = 0; int totalComparisons = 0;
//int round = 0; int isFirst = 0;
//
//void generateRandomData(int randomData[]) {
//	srand(time(0));
//	for (int i = 0; i < SIZE; i++) {
//		randomData[i] = rand() % 1000;
//	}
//}
//
//void printArray(int array[], int size) {
//	if (round % 10 == 0 && isFirst == 0) { // 10번에 한 번만 출력
//		for (int i = 0; i < 10; i++) // 0 ~ 9값
//			printf("%3d ", array[i]);
//		printf("| ");
//		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
//			printf("%3d ", array[i]);
//		printf("\n\n");
//	}
//}
//
//void merge(int list[], int left, int mid, int right) {
//	int i, j, k, l;
//	i = left; j = mid + 1; k = left;
//
//	while (i <= mid && j <= right) {
//		if (list[i] <= list[i]) {
//			totalComparisons++;
//			sorted[k++] = list[i++];
//			totalMoves++;
//		}
//		else {
//			sorted[k++] = list[j++];
//			totalMoves++;
//		}
//	}
//	if (i > mid) {
//		totalComparisons++;
//		for (l = j; l <= right; l++) {
//			sorted[k++] = list[l];
//			totalMoves++;
//		}
//	}
//	else
//		for (l = i; l <= mid; l++) {
//			sorted[k++] = list[l];
//			totalMoves++;
//		}
//	for (l = left; l <= right; l++) {
//		list[l] = sorted[l];
//		totalMoves++;
//	}
//}
//
//void merge_sort(int list[], int left, int right) {
//	int mid;
//	if (left < right) {
//		mid = (left + right) / 2;
//		merge_sort(list, left, mid);
//		merge_sort(list, mid + 1, right);
//		merge(list, left, mid, right);
//	}
//}
//
//int main() {
//	int array[SIZE];
//	
//	for (int i = 0; i < 20; i++) {
//		generateRandomData(array);
//		int comparisonCount = 0;
//		int moveCount = 0;
//
//		if (i = 0) {
//			/*printf("Merge Sort Run\n");
//			merge_sort(array, 0, SIZE - 1);*/
//
//			printf("Result\n");
//			printArray(array, SIZE);
//			isFirst++;
//		}
//		else {
//			/*merge_sort(array, 0, SIZE - 1);*/
//		}
//
//		totalComparisons += comparisonCount;
//		totalMoves += moveCount;
//	}
//	printf("\nAverage Comparisons: %.2f\n", totalComparisons/20.0);
//	printf("Average Moves: %.2f\n", totalMoves / 20.0);
//}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int sorted[SIZE];
int totalMoves = 0;
int totalComparisons = 0;
int round = 0;
int isFirst = 0;

void generateRandomData(int randomData[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % 1000;
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

void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        totalComparisons++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        totalMoves++;
    }

    while (i <= mid) {
        sorted[k++] = list[i++];
        totalMoves++;
    }

    while (j <= right) {
        sorted[k++] = list[j++];
        totalMoves++;
    }

    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
        totalMoves++;
    }
}

void merge_sort(int list[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main() {
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomData(array);

        if (i == 0) {
            printf("Initial Array:\n");
            printArray(array, SIZE);
            isFirst++;
        }

        merge_sort(array, 0, SIZE - 1);

        if (i == 0) {
            printf("Sorted Array:\n");
            printArray(array, SIZE);
        }
    }
    printf("Result\n");
    printallArray(array);

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
