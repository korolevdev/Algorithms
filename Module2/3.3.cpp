/**
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого
отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
**/
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Segment {
    int left;
    int right;
} Segment;

bool operator < (const Segment &p1, const Segment &p2) {
    return p1.left < p2.left;
}

template<class T>
bool compare(const T &obj1, const T &obj2) {
    return obj1 < obj2;
}

template<class T>
void swap(T *obj1, T *obj2) {
    T temp = *obj1;
    *obj1 = *obj2;
    *obj2 = temp;
}

template<class T>
void heap_make(T *a, int n, bool (*cmp) (const T &, const T &)) {
    for (int i = n/2; i >= 1; --i)
        for (int j = i; j <= n/2;) {
            int k = j*2;
            if (k + 1 <= n && compare(a[k], a[k+1]))
                ++k;

            if (compare(a[j], a[k])) {
                swap(&a[k], &a[j]);
                j = k;
            } else
                break;
        }
}

template<class T>
void heap_pop(T *a, int n, bool (*cmp) (const T &, const T &)) {
    swap(a[n], a[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if (i+1 < n && compare(a[i], a[i+1]))
            i += 1;

        if (compare(a[i/2], a[i]))
            swap(&a[i/2], &a[i]);
    }
}

template<class T>
void heap_sort_fast(T *data, int n, bool (*cmp) (const T &, const T &)) {
    heap_make(data - 1, n, cmp);
    for (int i = 0; i < n; ++i)
        heap_pop(data - 1, n - i, cmp);
}

int calc(Segment *a, int size) {
    Segment prev = a[0];
    int len = prev.right - prev.left;
    for (int i = 1; i < size; ++i) {
        if (a[i].left >= prev.right && a[i].right > prev.right) {
            len += a[i].right - a[i].left;
            prev = a[i];
        }

        if (a[i].left < prev.right && a[i].right > prev.right) {
            len += a[i].right - prev.right;
            prev.right = a[i].right;
        }

    }
    return len;
}

int main() {
    int size;
    cin >> size;

    Segment *arr = new Segment[size];

    for (int i = 0; i < size; ++i)
        cin >> arr[i].left >> arr[i].right;

    heap_sort_fast(arr, size, compare);

    cout << calc(arr, size);

    delete[] arr;

    return 0;
}


