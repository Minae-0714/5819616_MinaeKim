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
		randomData[i] = rand() % 10000;
	}
}

// 배열 출력
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++) // 처음 20개의 값
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++) // 마지막 20개의 값
		printf("%4d ", array[i]);
	printf("\n\n");
}

// 퀵 정렬에서 사용되는 파티션 함수 (배열을 피벗을 기준으로 두 부분으로 나누고, 피벗을 적절한 위치로 이동)
int partition(int list[], int left, int right) {
	int pivot = list[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (list[j] <= pivot) { // 현재 값이 피벗보다 작거나 같으면
			compareCount++;
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
void QuickSort(int list[], int left, int right) {
	if (left < right) {
		compareCount++;
		int q = partition(list, left, right);
		QuickSort(list, left, q - 1);
		QuickSort(list, q + 1, right);
	}
}

// 이진 탐색
int binarySearch(int array[], int key) {
	int low = 0, high = SIZE - 1, comparisons = 0;
	while (low <= high) { // 주어진 key 값 찾기
		//comparisons++;
		int mid = low + (high - low) / 2; // 중간 인덱스 계산
		if (array[mid] == key) { // 중간 값이 검색 키와 일치하는 경우
			comparisons++;
			return comparisons;
		}
		else if (array[mid] < key) { // 중간 값이 검색 키보다 작은 경우
			comparisons++;
			low = mid + 1;
		}
		else { // 중간 값이 검색 키보다 큰 경우
			comparisons++;
			high = mid - 1;
		}
	}
	return comparisons; // 비교 횟수 반환
}

// 이진 탐색 1000회 수행, 평균 비교 횟수 반환
float getAverageBinarySearchCompareCount(int array[]) {
	int totalComparisons = 0;
	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE]; // 배열에서 랜덤 값 선택
		totalComparisons += binarySearch(array, target); // 이진 탐색 후 비교 횟수 합산
	}
	return totalComparisons / 1000.0; // 평균 비교 횟수 반환
}

// 퀵 정렬 수행, 비교 횟수 기록
void getQuickSortCompareCount(int array[]) {
	compareCount = 0;
	QuickSort(array, 0, SIZE - 1);
}

// 보간 탐색
int interpolationSearch(int array[], int key) {
	int low = 0, high = SIZE - 1, comparisons = 0;
	while (low <= high && key >= array[low] && key <= array[high]) {
		//comparisons++;
		if (low == high) { // 만약 Low와 High가 같다면 배열에 하나의 값만 남은 상태
			comparisons++;
			if (array[low] == key) // 남은 값이 key와 일치하는지 확인
				return comparisons;
			break;
		}

		// 보간 공식
		int pos = low + ((double)(high - low) / (array[high] - array[low]) * (key - array[low]));

		if (array[pos] == key) { // pos 위치의 값이 key와 일치하면 검색 성공
			comparisons++;
			return comparisons;
		}
		else if (array[pos] < key) { // pos 위치의 값이 key보다 작으면 검색 범위를 오른쪽으로 축소
			comparisons++;
			low = pos + 1;
		}
		else { // pos 위치의 값이 key보다 크면 검색 범위를 왼쪽으로 축소
			comparisons++;
			high = pos - 1;
		}
	}
	return comparisons;
}

// 보간 탐색 1000회 수행, 평균 비교 횟수 반환
float getAverageInterpolationSearchCompareCount(int array[]) {
	int totalComparisons = 0;
	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE];
		totalComparisons += interpolationSearch(array, target);
	}
	return totalComparisons / 1000.0;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	QuickSort(array, 0, SIZE - 1);
	printArray(array);

	printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));

	printf("Average Compare Count of Interpolation Search: %.2f\n\n", getAverageInterpolationSearchCompareCount(array));

	return 0;
}