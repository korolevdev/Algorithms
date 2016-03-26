/**
В город ​приехал цирк с командой атлетов. Они хотят удивить горожан города ​— выстроить из своих тел
N​ N​ башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоин у него
на плечах, третий стоит на плечах у второго и т.д. Каждый атлет характеризуется силой ​s​m​ (kg) и массой  (kg).
Помогите им, напишите программу, которая определит максимальную высоту башни, которую они могут составить.
**/
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
