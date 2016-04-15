#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

void fill_matrix(long **a, int n) {
    for (int diagonal = 0; diagonal < n * 2 + 1; ++diagonal) {
        for (int m = 1; m <= diagonal + 1; ++m) {
            int n = diagonal - m + 1;

            if (n == 0) {
                a[n][m] = 1;
            } else {
                a[n][m] = 0;

                for (int j = 1; j <= n; ++j) {
                    int i = n - j;
                    if (j < m)
                        a[n][m] += a[i][j];
                }
            }
        }
    }
}

long** allocate_matrix(int n) {
    long **matrix = (long**) malloc(n*sizeof(long*));

    for (int i = 0; i < n; ++i) {
        matrix[i] = (long*) malloc(n*sizeof(long));
    }

    return matrix;
}

void free_matrix(long **a, int n) {
    if (!a)
        return;
    for (int i = 0; i < n; ++i)
        if (a[i] != NULL)
            free(a[i]);
    if (a != NULL)
        free(a);
}

int main() {
    int n;
    cin >> n;

    long **a = allocate_matrix(n * 2 + 1);

    fill_matrix(a, n);
    cout << (a[n][n] + 1);

    //free_matrix(a, n - 1);
    return 0;
}
