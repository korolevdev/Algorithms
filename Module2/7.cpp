#include <cstdio>
#include <vector>
#include <utility>
#include <functional>
#include <stdint.h>
#include <ctime>
#include <string.h>
#include <assert.h>
#include <cmath>
#include <iostream>

template <class T>
int findPivotIndex(T *a, size_t first, size_t last) {
    size_t mid = (first + last) / 2;

    if (a[mid] < a[first])
        std::swap(mid, first);
    if (a[last] < a[first])
        std::swap(last, first);
    if (a[last] < a[mid])
        std::swap(last, mid);

    a[mid].swap(a[last]);
    return last;
}

template <class T>
size_t Partition(T* arr, size_t begin, size_t end) {
    size_t pivotIndex = findPivotIndex(arr, begin, end);
    std::swap(arr[begin], arr[pivotIndex]);

    size_t i = begin + 1;
    size_t j = end;

    while (true) {
        while (arr[i] < arr[begin])
            ++i;

        while (arr[j] > arr[begin])
            --j;

        if (i < j) {
            arr[i].swap(arr[j]);
            ++i;
            --j;
        } else {
            arr[begin].swap(arr[i - 1]);
            return i - 1;
        }
    }
}

template<class T>
void insertionSort(T *data, int left, int right) {
    for (int i = left + 1; i < right; i++) {

        int l = 0, r = i;

        if (data[i] < data[i - 1]) {
            while (l < r) {
                int middle = (l + r) / 2;
                if (data[i] > data[middle])
                    l = middle + 1;
                else
                    r = middle;
            }
        } else
            continue;

        if (r < i - 1) {
            T temp = data[i];
            memmove(&data[r + 1], &data[r], (i - r) * sizeof(T));
            data[r] = temp;
        } else {
            data[i - 1].swap(data[i]);
        }
    }
}

template <class T>
void quickSortIterative(T *arr, int l, int h) {
    int stack[100000];
    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while ( top >= 0 ) {
        h = stack[top--];
        l = stack[top--];

        if (h - l <= 23500) { //  if (h - l <= 10) {
            insertionSort(arr + l, 0, h - l + 1);
            continue;
        }

        int p = Partition( arr, l, h );

        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

void sort(BlackInt *begin, BlackInt *end) {
    size_t n = end - begin;
    quickSortIterative(begin, 0, n - 1);
}