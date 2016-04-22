#include <cstdio>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

template<class T>
bool compare(const T &obj1, const T &obj2) {
    return obj1 <= obj2;
}

template<class T>
int64_t merge(T *arr, int first, int last, T *buf, bool (*compare) (const T &, const T &)) {
    if (last - first == 0)
        return 0;

    int half1_last = (last - first) / 2 + first;
    int half2_first = half1_last + 1;
    int64_t inv1 = merge(arr, first, half1_last, buf, compare);
    int64_t inv2 = merge(arr, half2_first, last, buf, compare);
    int64_t inv3 = 0;

    int j = first, k = half2_first;

    for (int i = first; i <= last; ++i)
        if (j <= half1_last && k <= last) {
            if (arr[j] <= arr[k]) {
                buf[i] = arr[j];
                ++j;
            } else {
                inv3 += (half1_last - j + 1);
                buf[i] = arr[k];
                ++k;
            }
        } else {
            if (j <= half1_last) {
                buf[i] = arr[j];
                ++j;
            } else {
                buf[i] = arr[k];
                ++k;
            }
        }

    for (int i = first; i <= last; ++i)
        arr[i] = buf[i];

    return inv1 + inv2 + inv3;
}

template<class T>
int64_t mergeSort(T *arr, int size, bool (*compare) (const T &, const T &)) {
    T *buf = (T*) malloc((size + 1) * sizeof(T));;
    int64_t inv = merge(arr, 0, size - 1, buf, compare);

    free(buf);
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

    int64_t inv = mergeSort(arr, i, compare);

    printf("%ld", inv);

    free(arr);
    return 0;
}
