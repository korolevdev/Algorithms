/**
Задано N точек на плоскости. Указать (N­1)­звенную несамопересекающуюся незамкнутую ломаную,
проходящую через все эти точки.
**/
#include <iostream>

using namespace std;

struct Point {
    int x;
    int y;
};

bool operator > (const Point &p1, const Point &p2) {
    return (p1.x == p2.x) ? p1.y > p2.y : p1.x > p2.x;
}

template<class T>
bool compare(const T &obj1, const T &obj2) {
    return obj1 > obj2;
}

template<class T>
void insertion_sort(T *arr, int n, bool (*cmp) (const T &, const T &)) {
    for (int i = 0; i < n; ++i) {
        T elem = arr[i];
        int j;
        for (j = i-1; j >= 0 && cmp(arr[j], elem); --j) {
            arr[j+1]= arr[j];
        }
        arr[j+1] = elem;
    }
}

int main() {
    int n;
    cin >> n;

    Point *arr = new Point[n];

    for (int i = 0; i < n; ++i)
        cin >> arr[i].x >> arr[i].y;

    insertion_sort(arr, n, compare);

    for (int i = 0; i < n; ++i)
        cout << arr[i].x << " " << arr[i].y << "\n";


    delete[] arr;
    
    return 0;
}


