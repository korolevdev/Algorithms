#include <cstdio>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t splitAndMerge(int *arr, int start, int end, int *buffer) {
    if (end - start == 0)
        return 0;

    int half1_end = (end - start) / 2 + start;
    int half2_start = half1_end + 1;
    int64_t inv1 = splitAndMerge(arr, start, half1_end, buffer);
    int64_t inv2 = splitAndMerge(arr, half2_start, end, buffer);
    int64_t inv3 = 0;

    int j = start, k = half2_start;

    for (int i = start; i <= end; ++i)
        if (j <= half1_end && k <= end) {
            if (arr[j] <= arr[k]) {
                buffer[i] = arr[j];
                ++j;
            } else {
                inv3 += (half1_end - j + 1);
                buffer[i] = arr[k];
                ++k;
            }
        } else {
            if (j <= half1_end) {
                buffer[i] = arr[j];
                ++j;
            } else {
                buffer[i] = arr[k];
                ++k;
            }
        }

    for (int i = start; i <= end; ++i)
        arr[i] = buffer[i];

    return inv1 + inv2 + inv3;
}

int64_t mergeSort(int *arr, int size) {
    int *buf = (int*) malloc((size + 1) * sizeof(int));;
    int64_t inv = splitAndMerge(arr, 0, size - 1, buf);
    return inv;
}

int main() {
    int alloc = 100, i = 0;
    int *arr = (int*) malloc(alloc * sizeof(int));

    while (scanf("%d", &arr[i]) != EOF) {
        i++;
        if (i > alloc) {
            alloc *= 2;
            arr = (int*) realloc(arr, alloc*sizeof(int));
        }
    }

    int64_t inv = mergeSort(arr, i);
    printf("%ld", inv);
    return 0;
}
