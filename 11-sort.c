#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))

void generateRandomData(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        randomData[i] = rand() % 1000;
    }
}

void print_sort(int randomData[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", randomData[i]);
    }
    printf("\n");
}

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

        // i 이후의 최솟값을 찾음
        for (j = i + 1; j < SIZE; j++) {
            if (list[least] > list[j]) {
                least = j;
            }
        }

        // 최소값 위치가 i와 다르면 교환 수행
        if (least != i) {
            SWAP(list[i], list[least], temp);
        }

        if ((i + 11) % 10 == 0 && (i + 11) % 20 == 0) {
            printf("Step %d: ", i + 1);
            print_sort(list);
            printf("\n");
        } 
        
        final_step = i;

        int isSortedCorrectly = 1;
        for (int i = 0; i < SIZE - 1; i++) {
            if (list[i] > list[i + 1]) {
                isSortedCorrectly = 0;  // 오름차순이 아니면
                break;
            }
        }
        if (isSortedCorrectly == 1)
            break;
    }
    printf("Step %d: ", final_step + 1);
    print_sort(list);
}


void doInsertionSort(int original[]) {
    int totalComparisons = 0;
    int list[SIZE];

    for (int run = 0; run < 20; run++) {
        for (int i = 0; i < SIZE; i++) {
            list[i] = original[i];
        }

        int comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            int key = list[i];
            int j = i - 1;

            while (j >= 0 && list[j] > key) {
                comparisons++;
                list[j + 1] = list[j];
                j--;
            }
            comparisons++;
            list[j + 1] = key;
        }
        totalComparisons += comparisons;
    }
    printf("\n");
    printf("Insertion Sort Compare Average: %d\n", totalComparisons / 20);
    printf("Insertion Sort Result:\n");
    print_sort(list);
}

void doBubbleSort(int original[]) {
    int totalMovements = 0;
    int list[SIZE];

    for (int run = 0; run < 20; run++) {
        for (int i = 0; i < SIZE; i++) {
            list[i] = original[i];
        }

        int movements = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (list[j] > list[j + 1]) {
                    int temp;
                    SWAP(list[j], list[j + 1], temp);
                    movements += 3; // Count each swap as 3 moves
                }
            }
        }
        totalMovements += movements;
    }
    printf("\n");
    printf("Bubble Sort Move Average: %d\n", totalMovements / 20);
    printf("Bubble Sort Result:\n");
    print_sort(list);
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

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#define SIZE 100
//
//#define SWAP(x,y,t)((t)=(x),(x)=(y), (y)=(t))
//
//void generateRandomData(int randomData[]) {
//    for (int i = 0; i < SIZE; i++) {
//        randomData[i] = rand() % 1000;
//    }
//}
//
//void print_sort(int randomData[]) {
//    for (int i = 0; i < SIZE; i++) {
//        printf("%d ", randomData[i]);
//    }
//    printf("\n");
//}
//
//void doSelectionSort(int original[]) {
//    int list[SIZE];
//    for (int i = 0; i < SIZE; i++) {
//        list[i] = original[i];
//    }
//    int j, least, temp;
//
//    printf("Selection Sort:\n");
//
//    for (int i = 0; i < SIZE - 1; i++) {
//        least = i;
//
//        // Find the minimum element in unsorted part
//        for (j = i + 1; j < SIZE; j++) {
//            if (list[least] > list[j]) {
//                least = j;
//            }
//        }
//
//        // Swap if a new minimum is found
//        if (least != i) {
//            SWAP(list[i], list[least], temp);
//        }
//    }
//    printf("Final sorted array (Selection Sort): ");
//    print_sort(list);
//}
//
//void doInsertionSort(int original[]) {
//    srand(time(0));
//    int totalComparisons = 0;
//    int list[SIZE];
//
//    printf("\nInsertion Sort (20 runs):\n");
//    for (int run = 0; run < 20; run++) {
//        generateRandomData(list);  // Fresh random data for each run
//
//        int comparisons = 0;
//        for (int i = 1; i < SIZE; i++) {
//            int key = list[i];
//            int j = i - 1;
//
//            while (j >= 0 && list[j] > key) {
//                comparisons++;
//                list[j + 1] = list[j];
//                j--;
//            }
//            comparisons++;
//            list[j + 1] = key;
//        }
//        totalComparisons += comparisons;
//
//        printf("Run %d sorted array: ", run + 1);
//        print_sort(list);
//    }
//    printf("Average comparisons in Insertion Sort: %d\n", totalComparisons / 20);
//}
//
//void doBubbleSort(int original[]) {
//    srand(time(0));
//    int totalMovements = 0;
//    int list[SIZE];
//
//    printf("\nBubble Sort (20 runs):\n");
//    for (int run = 0; run < 20; run++) {
//        generateRandomData(list);  // Fresh random data for each run
//
//        int movements = 0;
//        for (int i = 0; i < SIZE - 1; i++) {
//            for (int j = 0; j < SIZE - i - 1; j++) {
//                if (list[j] > list[j + 1]) {
//                    int temp;
//                    SWAP(list[j], list[j + 1], temp);
//                    movements += 3; // Count each swap as 3 moves
//                }
//            }
//        }
//        totalMovements += movements;
//
//        printf("Run %d sorted array: ", run + 1);
//        print_sort(list);
//    }
//    printf("Average movements in Bubble Sort: %d\n", totalMovements / 20);
//}
//
//int main() {
//    int randomData[SIZE];
//    generateRandomData(randomData);
//
//    doSelectionSort(randomData);
//    doInsertionSort(randomData);
//    doBubbleSort(randomData);
//
//    return 0;
//}
