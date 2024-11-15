#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 100

#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

void generateRandomData(int randomData[]) {
    srand(time(0));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        randomData[i] = rand() % 1000;
    }
}

void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int temp, i, j, gap;
    int n = ARRAY_SIZE;

    *comparisonCount = 0;
    *moveCount = 0;

    gap = (gapType == 2) ? n / 2 : n / 3;

    while (gap > 0) {
        for (i = gap; i < n; i++) {
            temp = array[i];
            j = i;

            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
                (*comparisonCount)++;
                (*moveCount)++;
            }
            array[j] = temp;
            if (j != i) {
                (*moveCount)++;
            }
        }

        printf("Sorting with gap = %d:\n ", gap);
        printArray(array);

        gap = (gapType == 2) ? gap / 2 : (gap > 1) ? gap / 3 : 0;
    }
}


int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomData(array);

    printf("Shell Sort (n/2): \n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    /* printf("Shell Sort (n/3): \n");
     doShellSort(array, 3, &comparisonCount, &moveCount);
     printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);*/
}