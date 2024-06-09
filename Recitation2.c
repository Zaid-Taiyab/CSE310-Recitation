#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int arrSize;

void insertionSort(double A[]);
void selectionSort(double A[]);
void mergeSort(double arr[], int l, int r);
void quickSort(double arr[], int l, int r);

void insertionSort(double A[]) {
    double key;
    for (int i = 1; i < arrSize; ++i) {
        key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

void selectionSort(double A[]){
    for(int i=1;i<arrSize;++i){
        for(int j=i+1;j<arrSize;++j){
            if (A[j]<A[i]){
                double temp=A[j];
                A[j]=A[i];
                A[i]=temp;
            }
        }
    }
}

void merge(double arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    double *L = (double *)malloc(n1 * sizeof(double));
    double *R = (double *)malloc(n2 * sizeof(double));
    for (int i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[q + 1 + j];
    }
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(double A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int partition(double arr[], int p, int r) {
    double pivot = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (arr[j] < pivot) {
            i++;
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    double temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}

void quickSort(double A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

void generateRandomArray(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 100.0 + ((double)rand() / RAND_MAX) * (1000.0 - 100.0);
    }
}

void copyArray(double source[], double destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

int main() {
    srand(time(0));
    int sizes[] = {10000, 25000, 50000, 100000, 150000, 200000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    printf("Array Size,Insertion Sort,Selection Sort,Merge Sort,Quick Sort\n");
    for (int i = 0; i < numSizes; i++) {
        arrSize = sizes[i];
        double *arr = (double *)malloc(arrSize * sizeof(double));
        double *arrCopy = (double *)malloc(arrSize * sizeof(double));
        generateRandomArray(arr, arrSize);
        copyArray(arr, arrCopy, arrSize);
        clock_t start = clock();
        insertionSort(arrCopy);
        clock_t end = clock();
        double timeInsertion = (double)(end - start) / CLOCKS_PER_SEC;
        copyArray(arr, arrCopy, arrSize);
        start = clock();
        selectionSort(arrCopy);
        end = clock();
        double timeSelection = (double)(end - start) / CLOCKS_PER_SEC;
        copyArray(arr, arrCopy, arrSize);
        start = clock();
        mergeSort(arrCopy, 0, arrSize - 1);
        end = clock();
        double timeMerge = (double)(end - start) / CLOCKS_PER_SEC;
        copyArray(arr, arrCopy, arrSize);
        start = clock();
        quickSort(arrCopy, 0, arrSize - 1);
        end = clock();
        double timeQuick = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d,%.6f,%.6f,%.6f,%.6f\n", arrSize, timeInsertion, timeSelection, timeMerge, timeQuick);
        free(arr);
        free(arrCopy);
    }
    return 0;
}
