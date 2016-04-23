#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>
#include <functional>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <cmath>

template <class T>
int findPivotIndex(T *a, size_t first, size_t last) {
    size_t mid = (first + last) / 2;

    if (a[mid] < a[first])
        a[first].swap(a[mid]);
    if (a[last] < a[first])
        a[first].swap(a[last]);
    if (a[last]< a[mid ])
        a[mid].swap(a[last]);

    a[mid].swap(a[last - 1]);
    return last - 1;
}

template <class T>
size_t Partition(T* arr, size_t begin, size_t end) {
    size_t pivotIndex = findPivotIndex(arr, begin, end);
    std::swap(arr[begin], arr[pivotIndex]);
    T pivot = arr[begin];

    size_t i = begin + 1;
    size_t j = end;

    while (true) {
        while (arr[i] < pivot)
            ++i;

        while ( arr[j] > pivot)
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
void insertionSort (T *input, size_t lo, size_t hi)
{
    for (size_t i = lo + 1; i < hi; ++i) {
        for (int j = i; j > lo && input[j] < input[j-1]; --j) {
           input[j].swap(input[j-1]);
        }
    }
}

template<class T>
void heap_make(T *a, int n) {
    for (int i = n/2; i >= 1; --i)
        for (int j = i; j <= n/2;) {
            int k = j*2;
            if (k + 1 <= n && a[k] < a[k+1])
                ++k;

            if (a[j] < a[k]) {
                a[k].swap(a[j]);
                j = k;
            } else
                break;
        }
}

template<class T>
void heap_pop(T *a, int n) {
    a[n].swap(a[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if (i+1 < n && a[i] < a[i+1])
            i += 1;

        if (a[i/2] < a[i])
            a[i/2].swap(a[i]);
    }
}

template<class T>
void heap_sort_fast(T *data, int n) {
    heap_make(data - 1, n);
    for (int i = 0; i < n; ++i)
        heap_pop(data - 1, n - i);
}

template <class T>
void quickSortIterative(T *arr, int l, int h) {
    int stack[100000];
    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while ( top >= 0 ) {
        h = stack[ top-- ];
        l = stack[ top-- ];

        if (l >= h)
            continue;

        if (h - l <= 15000) {
            heap_sort_fast(arr + l, h - l + 1);
            continue;
        }

        int p = Partition( arr, l, h );

        if ( p - 1 > l ) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        if ( p + 1 < h ) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

void sort(BlackInt *begin, BlackInt *end) {
    size_t n = end - begin;
    quickSortIterative(begin, 0, n - 1);
}
