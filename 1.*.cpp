/**
 Найти все простые числа в диапазоне [2..n] за O(n).
**/
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void find_primes(bool *isPrimes, int limit) {
    double sqrLimit = sqrt(limit);
    for (int x = 1; x <= sqrLimit; x++)
        for (int y = 1; y <= sqrLimit; y++) {
            int x2 = x*x;
            int y2 = y*y;
            int n = 4*x2 + y2;
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                isPrimes[n] ^= true;

            n -= x2;
            if (n <= limit && n % 12 == 7)
                isPrimes[n] ^= true;

            n -= 2 * y2;
            if (x > y && n <= limit && n % 12 == 11)
                isPrimes[n] ^= true;
        }

    for (int n = 5; n <= sqrLimit; n += 2)
        if (isPrimes[n]) {
            int s = n*n;
            for (int k = s; k <= limit; k += s)
                isPrimes[k] = false;
        }
    isPrimes[2] = true;
    isPrimes[3] = true;
}

int main() {
    int limit;
    cin >> limit;

    bool *isPrimes = new bool[limit + 1];

    // Инициализация решета
    for (int i = 0; i <= limit; i++)
        isPrimes[i] = false;
    isPrimes[2] = true;
    isPrimes[3] = true;

    // Предположительно простые - это целые с нечетным числом
    // представлений в данных квадратных формах.
    // x2 и y2 - это квадраты i и j (оптимизация).
    find_primes(isPrimes, limit);

    for (int i = 1; i <= limit; i++) {
        if ((isPrimes[i])){
            cout << i << " ";
        }
    }
    delete[] isPrimes;
    return 0;
}
