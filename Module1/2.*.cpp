#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

int find_repeat(int *a, int n) {
    int current = a[n - 1];
    for (int i = 0; i < n - 1; ++i) {
        current = a[current];
    }

    int pos = a[current];
    int cycleLen = 1;
    while (pos != current) {
        cycleLen++;
        pos = a[pos];
    }

    current = pos = a[n - 1];
    for (int i = 0; i < cycleLen; ++i)
        pos = a[pos];

    while (current != pos) {
        current = a[current];
        pos = a[pos];
    }

    return current;
}

int main() {
    int n;
    cin >> n;

    int *a = new int[n];

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    cout << find_repeat(a, n);

    delete[] a;
    return 0;
}
