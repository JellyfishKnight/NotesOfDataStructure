#include <iostream>

using namespace std;


void mergeSort(int* a, int lowerBound, int middle, int upperBound) {
    int lb = middle - lowerBound;
    int b[lb];
    for (int i = 0; i < lb; i++) {
        b[i] = a[lowerBound + i];
    }
    int lc = upperBound - middle;
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (k >= lc || (b[j] < a[middle + k]))) {
            a[lowerBound + i++] = b[j++];
        }
        if ((k < lc) && (j >= lb || (a[middle + k] < b[j]))) {
            a[lowerBound + i++] = a[middle + k++];
        }
    }
}

void mergeSort(int *a, int lowerBound, int upperBound) {
    if (upperBound - lowerBound < 2) {
        return;
    }
    int middle = (lowerBound + upperBound) / 2;
    mergeSort(a, lowerBound, middle);
    mergeSort(a, middle, upperBound);
    mergeSort(a, lowerBound, middle, upperBound);
}
