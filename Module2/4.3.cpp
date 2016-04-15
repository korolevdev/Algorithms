/**
4_3.​Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition
реализуйте методом прохода двумя итераторами от начала массива к концу.
**/
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct IntNum {
    int value;
} IntNum;

template<class T>
void swap(T *obj1, T *obj2) {
    T temp = *obj1;
    *obj1 = *obj2;
    *obj2 = temp;
}

bool operator <= (const IntNum &p1, const IntNum &p2) {
    return p1.value <= p2.value;
}

template<class T>
bool compare(const T &obj1, const T &obj2) {
    return obj1 <= obj2;
}

template<class T>
int partition(T *arr, int left, int right, bool (*cmp) (const T &, const T &)) {
    if (left != right)
        swap(&arr[left + rand() % (right - left)], &arr[right]);
    const T& x = arr[right];
    int i = left - 1;
    for (int j = left; j <= right; j++) {
        if (cmp(arr[j], x))
            swap(&arr[++i], &arr[j]);
    }
    return i;
}

template<class T>
const T& nth(T *arr, int size, int k, bool (*cmp) (const T &, const T &)) {
    int left = 0, right = size - 1;
    for (;;) {
        int pos = partition(arr, left, right, cmp);
        if (pos < k)
            left = pos + 1;
        else
            if (pos > k)
                right = pos - 1;
            else
                return arr[k];
    }
}

int main() {
    int size, k;
    cin >> size >> k;

    IntNum *arr = new IntNum[size];
    for (int i = 0; i < size; ++i)
        cin >> arr[i].value;

    IntNum num = nth(arr, size, k, compare);
    cout << num.value;

    delete[] arr;

    return 0;
}



