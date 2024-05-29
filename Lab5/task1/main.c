#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Array manipulation functions
int * generate_random_array(int size);
void print_array(int *array, int size);
void free_array(int *array);
int* copy_array(int* array, int size);

// Inneficent sorting algorithms
void selection_sort(int *array, int size);
void insertion_sort(int *array, int size);
void bubble_sort(int *array, int size);

// Efficient sorting algorithms
void merge_sort(int *array, int left, int right);
void quick_sort(int *array, int low, int high);
void heap_sort(int *array, int size); // Looks like this one is quick even with 10M elements. Nice :D

// Opens the menu for benchmarking sorting algorithms
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
        array[i] = rand() % 100;
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

void selection_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }


        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}

void insertion_sort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void merge(int *array, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void quick_sort(int *array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
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

    while (1) {
        printf("\n1. Selection Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Bubble Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        clock_t start, end;
        double cpu_time_used;

        int *copy = copy_array(array, size);
        if (copy == NULL) {
            printf("Failed to allocate memory for array copy\n");
            continue;
        }

        switch (choice) {
            case 1:
                start = clock();
                selection_sort(copy, size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Selection Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 2:
                start = clock();
                insertion_sort(copy, size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Insertion Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 3:
                start = clock();
                bubble_sort(copy, size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Bubble Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 4:
                start = clock();
                merge_sort(copy, 0, size - 1);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Merge Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 5:
                start = clock();
                quick_sort(copy, 0, size - 1);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Quick Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 6:
                start = clock();
                heap_sort(copy, size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Array after Heap Sort:\n");
                print_array(copy, size);
                printf("Time taken: %f seconds\n", cpu_time_used);
                break;
            case 7:
                free_array(array);
                return;
            default:
                printf("Invalid choice\n");
        }
        free_array(copy);
    }
}