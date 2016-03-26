/**
Дан массив целых чисел A[0..n). Не используя других массивов переставить элементы массива A  в обратном порядке за O(n). 
**/
#include <iostream>

using namespace std;

// Переворачивание массива
void reverse(int *a, int n) {
    for (int i = 0; i < n / 2; ++i) {
        int temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    reverse(a, n);
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    return 0;
}


