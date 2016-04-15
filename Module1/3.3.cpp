#include <iostream>
#include <cassert>

using namespace std;

int binfind(int *a, int x, int left, int right) {
    if (left > right) {
        return -1;
    }

    int mid = (static_cast<unsigned>(left) + static_cast<unsigned>(right)) >> 1;

    if (a[mid] == x)
        return mid;
    if (a[mid] < x)
        return binfind(a, x, mid + 1, right);
    if (a[mid] > x)
        return binfind(a, x, left, mid - 1);

    return -1;
}

void calc(int *a, int *b, int *c, int n, int m, int *size) {
    int pos_k, left, right;

    pos_k = 1;
    assert(n > 1);
    while (a[pos_k] < b[m - 1]) {
        pos_k *= 2;
        if (pos_k > n - 1) {
            pos_k = n - 1;
            break;
        }
    }

    left = 0;
    right = pos_k;
    for (int i = 0; i < m; ++i) {
        int pos = binfind(a, b[i], left, right);
        if (pos != -1) {
            c[(*size)++] = b[i];
            left = pos;
        }
    }
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    int *a = new int[n];
    int *b = new int[m];
    int *c = new int[m];
    int size = 0;

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    calc(a, b, c, n, m, &size);

    for (int i = 0; i < size; ++i)
        cout << c[i] << " ";

    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}


