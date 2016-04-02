#include <iostream>

using namespace std;

// Решение задачи Иосифа Флавия
int joseph(int n, int k) {
    return n > 1 ? (joseph(n - 1, k) + k - 1) % n + 1 : 1;
}

int joseph_2(int n, int k) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result = (result + k - 1) % i + 1;
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << joseph(n, k);
    cout << "\n";
    cout << joseph_2(n, k);
    return 0;
}


