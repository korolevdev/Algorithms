/*
Дан массив строк. Количество строк не больше 10
Размер алфавита ­ 256 символов. Последний символ строки = ‘\0’.
Отсортировать массив методом поразрядной cортировки MSD по символам.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define ALPHA 256

using namespace std;

void msd_sort(vector<string>::iterator first, vector<string>::iterator last, int offset) {
    vector<vector<string>> buf(ALPHA);

    for (vector<string>::iterator i = first; i != last; ++i)
        buf[static_cast<int>((*i)[offset])].push_back(*i);

    for (int i = 1; i < ALPHA; ++i) 
        if (buf[i].size() > 1)
            msd_sort(buf[i].begin(), buf[i].end(), offset + 1);
    
    int k = 0;
    for (vector<string>::iterator i = first; i != last;) {
        for (vector<string>::iterator j = buf[k].begin(); j != buf[k].end(); ++j)
            *i++ = *j;
        ++k;
    }
}

int main() {
    string buf;
    vector<string> items;

    cin >> buf;
    while (!cin.eof()) {
        if (!buf.empty())
            items.push_back(buf);

        buf.clear();
        cin >> buf;
    }

    msd_sort(items.begin(), items.end(), 0);

    for (vector<string>::iterator i = items.begin(); i != items.end(); ++i)
        cout << *i << endl;

    return 0;
}