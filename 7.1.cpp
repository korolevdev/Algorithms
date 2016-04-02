#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_SIZE 100000

using namespace std;

long calc(int *mass, int *power, int n) {
    sort(mass, mass + n);
    sort(power, power + n);

    long curMass = mass[0], curHeight = 1;

    for (size_t i = 1; i < n; i++)
        if (power[i] >= curMass) {
            curMass += mass[i];
            curHeight++;
        }
    return curHeight;
}

int main() {
    int *mass = new int[MAX_SIZE];
    int *power = new int[MAX_SIZE];

    int i = 0;
    int j = 0;
    while (scanf("%ld %ld", &mass[i++], &power[j++]) == 2);

    cout << (calc(mass, power, i));

    delete[] mass;
    delete[] power;

    return 0;
}
