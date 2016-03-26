/**
 “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N. Будем исключать каждого k­ого до тех пор,
 пока не уцелеет только один человек. (Например, если N=10, k=3, то сначала умрет 3­й, потом 6­й, затем 9­й, затем 2­й, затем 7­й,
 потом 1­й, потом 8­й, за ним ­ 5­й, и потом 10­й. Таким образом, уцелеет 4­й.) Необходимо определить номер уцелевшего.
**/
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


