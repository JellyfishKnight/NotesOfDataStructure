#include <iostream>

void BubbleSort(int *a, int lower_bound, int upper_bound) {
    for (int i = lower_bound; i < upper_bound; i++) {
        for (int j = i; j < upper_bound; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}