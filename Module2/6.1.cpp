#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define ALPH 256

using namespace std;

typedef std::vector<std::string> strings;

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

int main() {
    int max = 0, j = 0;
    char c;
    std::string buffer;
    strings words;
    std::cin >> buffer;
    while (!std::cin.eof())
    {
        if (!buffer.empty())
        {
            words.push_back(buffer);
        }
        buffer.clear();
        std::cin >> buffer;
    }

    sort(words.begin(), words.end());
    //radix_msd_sort(words.begin(), words.end(), 0);
    
    for (strings::iterator i = words.begin(); i != words.end(); ++i)
        std::cout << *i << std::endl;


    return 0;
}
