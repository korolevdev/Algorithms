#include <iostream>
#include <stdio.h>
#include <algorithm>
#define ALPH 256

using namespace std;

//radixSort(arr, 0, arr.length - 1, 1)
void radixSort(char **arr, int left, int right, int d, int max) {
    int *cnt = new int[ALPH];
    int i, j;

    char **c = (char**) calloc(right + 2, sizeof(char*));

    if (d > max || left >= right)
        return;

    for (j = 0; j <= ALPH + 1; ++j)
        cnt[j] = 0;

    for (i = left; i <= right; ++i) {
        j = arr[i][d];
        cnt[j + 1]++;
    }
    for (j = 2; j <= ALPH; j++)
        cnt[j] += cnt[j - 1];

    for (i = left; i <= right; ++i) {
        j = arr[i][d];
        c[left + cnt[j]] = arr[i];
        cnt[j]++;
    }

    for (i = left; i <= right; ++i)
        arr[i] = c[i];
    free(c);

    radixSort(arr, left, left + cnt[0] - 1, d + 1, max);
    for (int i = 1; i <= ALPH; ++i)
        radixSort(arr, left + cnt[i - 1], left + cnt[i] - 1, d + 1, max);
}

void free_matrix(char **mtx, size_t n) {
    if (!mtx)
        return;
    for(size_t i = 0; i < n; ++i)
        if (mtx[i])
            free(mtx[i]);

    free(mtx);
}

char** alloc_matrix(size_t n, size_t m) {
    char **mtx = (char**) calloc(n, sizeof(char*));
    if (!mtx)
        return NULL;
    for (size_t i = 0; i < n; ++i) {
        mtx[i] = (char*) calloc(m, sizeof(char));
        if (!mtx[i]) {
            free_matrix(mtx, i);
            return NULL;
        }
    }
    return mtx;
}

int main() {
    int size = 0;

    int max = 0, j = 0;
    char c;
    char **arr = alloc_matrix(1000, 1000);

    freopen ("in.txt", "r", stdin);

    while (scanf("%c", &c) != EOF) {
        if (c == '\n') {
            arr[size++][j++] = '\0';
            if (j > max)
                max = j;
            j = 0;
        } else
            arr[size][j++] = c;
    }
    arr[size++][j++] = '\0';
    if (j > max)
        max = j;

    radixSort(arr, 0, size - 1, 0, max);

    for (int i = 1; i < size; ++i) {
        j = 0;
        while (arr[i][j] != '\0')
            cout << arr[i][j++];
        cout << "\n";
    }

    free_matrix(arr, size);

    return 0;
}