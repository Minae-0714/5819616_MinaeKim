#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

int totalComparisons = 0;
int compareCount = 0;

// 랜덤 배열 생성
void generateRandomArray(int randomData[]) {
	for (int i = 0; i < SIZE; i++) {
		randomData[i] = rand() % 1000;
	}
}

// 배열 출력
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++) // 처음 20개의 값
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++) // 마지막 20개의 값
		printf("%3d ", array[i]);
	printf("\n");
}

// 선형 탐색
int linearSearch(int array[], int key) {
	int comparisons = 0;
	for (int i = 0; i < SIZE; i++) { // 배열에서 주어진 key값 찾고
		comparisons++;
		if (array[i] == key) {
			return comparisons; // 비교횟수 반환
		}
	}
}

// 선형 탐색 100번 수행 후 평균 비교 횟수 반환
float getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    
    for (int i = 0; i < 100; i++) { // 선형 탐색 100번 수행
        int randomIndex = rand() % SIZE;  
        int randomKey = array[randomIndex];
        totalComparisons += linearSearch(array, randomKey); 
    }
    
    return totalComparisons / 100.0; // 비교 횟수 반환
}

// 퀵 정렬에서 사용되는 파티션 함수 (배열을 피벗을 기준으로 두 부분으로 나누고, 피벗을 적절한 위치로 이동)
int partition(int list[], int left, int right) {
	int pivot = list[right];
	int i = left - 1;

	for (int j = left; j < right; j++) {
		compareCount++; 
		if (list[j] <= pivot) { // 현재 값이 피벗보다 작거나 같으면
			i++; // 피벗보다 작은 값
			int temp = list[i];
			list[i] = list[j];
			list[j] = temp; // SWAP
		}
	}

	// 피벗을 올바른 위치로 이동
	int temp = list[i + 1];
	list[i + 1] = list[right];
	list[right] = temp;

	return i + 1; // 피벗의 최종 위치 반환
}

// 퀵 정렬 함수
void doQuickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		doQuickSort(list, left, q - 1);
		doQuickSort(list, q + 1, right);
	}
}

// 이진 탐색
int binarySearch(int array[], int key) {
	int low = 0, high = SIZE - 1, comparisons = 0;
	while (low <= high) { // 주어진 key 값 찾기
		comparisons++;
		int mid = low + (high - low) / 2;
		if (array[mid] == key)
			return comparisons;
		else if (array[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return comparisons; // 비교 횟수 반환
}

// 이진 탐색 100회 수행, 평균 비교 횟수 반환
float getAverageBinarySearchCompareCount(int array[]) {
	int totalComparisons = 0;
	for (int i = 0; i < 100; i++) {
		int randomIndex = rand() % SIZE; // 배열에서 랜덤 값 선택
		int randomKey = array[randomIndex];
		totalComparisons += binarySearch(array, randomKey); // 이진 탐색 후 비교 횟수 합산
	}
	return totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 퀵 정렬 수행, 비교 횟수 기록
void getQuickSortCompareCount(int array[]) {
	compareCount = 0;
	doQuickSort(array, 0, SIZE - 1); 
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];

	generateRandomArray(array);

	//평균값을 반환받기 위한 조치
	printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));
	
	//compareCount가 global variavble이므로, 다음과 같이 구현
	//array에 대해서 직접 정렬하면 됨
	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);

	//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
	printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));
	printArray(array);

	return 0;
}