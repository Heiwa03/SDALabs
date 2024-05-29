#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int * generate_random_array(int size);
void print_array(int *array, int size);
void free_array(int *array);
int* copy_array(int* array, int size);

double linear_search(int* array, int size, int target);
double binary_search(int* array, int size, int target); // Only works for sorted arrays

void open_menu() ;

int main() {
    srand(time(0));
    open_menu();
    return 0;
}

int * generate_random_array(int size) {
    int *array = (int *) malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;
    }
    return array;
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void free_array(int *array) {
    free(array);
}

int* copy_array(int* array, int size) {
    int* copy = (int*) malloc(size * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        copy[i] = array[i];
    }

    return copy;
}

double linear_search(int* array, int size, int target) {
    clock_t start, end;
    start = clock();

    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            end = clock();
            return ((double) (end - start)) / CLOCKS_PER_SEC;
        }
    }

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double binary_search(int* array, int size, int target) {
    clock_t start, end;
    start = clock();

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == target) {
            end = clock();
            return ((double) (end - start)) / CLOCKS_PER_SEC;
        }

        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void heapify(int *array, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest])
        largest = left;

    if (right < size && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        int swap = array[i];
        array[i] = array[largest];
        array[largest] = swap;

        heapify(array, size, largest);
    }
}

// Needed for soring the array. Also provieds a worst case scenario for the linear algorithms
void heap_sort(int *array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (int i = size - 1; i >= 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
    }
}

void open_menu() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *array = generate_random_array(size);
    if (array == NULL) {
        return;
    }

    printf("Generated array:\n");
    print_array(array, size);

    int target;
    printf("Enter the target value to search for: ");
    scanf("%d", &target);

    while (1) {
        printf("\n1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        double time_taken;
        int *copy = NULL;

        switch (choice) {
            case 1:
                copy = copy_array(array, size);
                if (copy == NULL) {
                    printf("Failed to allocate memory for array copy\n");
                    continue;
                }
                heap_sort(copy, size);
                time_taken = linear_search(copy, size, target);
                printf("Time taken for Linear Search: %f seconds\n", time_taken);
                free(copy);
                copy = NULL;
                break;
            case 2:
                copy = copy_array(array, size);
                if (copy == NULL) {
                    printf("Failed to allocate memory for array copy\n");
                    continue;
                }
                heap_sort(copy, size);
                time_taken = binary_search(copy, size, target);
                printf("Time taken for Binary Search: %f seconds\n", time_taken);
                free(copy);
                copy = NULL;
                break;
            case 3:
                free_array(array);
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}