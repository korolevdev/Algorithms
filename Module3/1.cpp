/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
Хранимые строки непустые и состоят из строчных латинских букв. Начальный размер таблицы должен быть равным 8-ми. 
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, 
удаления строки из множества и проверки принадлежности данной строки множеству.

Для разрешения коллизий используйте двойное хеширование.
*/
#include <iostream>
#include <string>
#include <vector>
#define INIT_SIZE 8
#define HASH_A 37
#define HASH_2 59
#define REHASH 3.0 / 4.0

using namespace std;

int hash_a(string s, int m) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i)
        result = (result * HASH_A + s[i]) % m;

    return result;
}

int hash_b(string s, int m) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i)
        result = (result * HASH_2 + s[i]) % m;

    return (2 * result + 1) % m;
}

struct Node {
    string Data;
    bool isDeleted;

    Node(string data) : Data(data), isDeleted(false) {}
};


class Table {
public:
    Table() : alloc(INIT_SIZE), size(0), map(INIT_SIZE, NULL) {}
    ~Table();

    bool Add(string);
    bool Remove(string);
    bool Has(string);

private:
    vector<Node*> map;
    int alloc;
    int size;
    void rehash();
};

bool Table::Has(string s) {
    int hashA = hash_a(s, alloc);
    int hashB = hash_b(s, alloc);
    int i = 0;

    while (map[hashA] != NULL && i < alloc) {
        if (map[hashA]->Data == s && !map[hashA]->isDeleted) {
            return true;
        }
        hashA = (hashA + hashB) % alloc;
        i++;
     }
    return false;
}

bool Table::Add(string s) {
    if ((float) size / (float) alloc >= REHASH)
        rehash();
    
    int hashA = hash_a(s, alloc);
    int hashB = hash_b(s, alloc);

    int i = 0;
    int deletedNodeIndex = -1;
    while (map[hashA] != NULL && i < alloc) {
        if (map[hashA]->Data == s && !map[hashA]->isDeleted) 
            return false;
        
        if (map[hashA]->isDeleted && deletedNodeIndex < 0)
            deletedNodeIndex = hashA;
        
        hashA = (hashA + hashB) % alloc;
        ++i;
    }

    if (deletedNodeIndex >= 0) {
        map[deletedNodeIndex]->Data = s;
        map[deletedNodeIndex]->isDeleted = false;
    } else 
        map[hashA] = new Node(s);

    size++;
    return true;
}

bool Table::Remove(string s) {
    int hashA = hash_a(s, alloc);
    int hashB = hash_b(s, alloc);

    int i = 0;
    while (map[hashA] != NULL && i < alloc) {
        if (map[hashA]->Data == s && !map[hashA]->isDeleted) {
            map[hashA]->isDeleted = true;
            size--;
            return true;
        }
        hashA = (hashA + hashB) % alloc;
        ++i;
    }
    return false;
}

void Table::rehash() {
    int newSize = alloc * 2;
    vector<Node*> newMap(newSize, NULL);
    for (int i = 0; i < alloc; ++i) {
        if (map[i] != NULL && !map[i]->isDeleted) {
            string data = map[i]->Data;
            int currentHash = hash_a(data, newSize);
            int anotherHash = hash_b(data, newSize);
            int j = 0;

            while (newMap[currentHash] != NULL && j < newSize) {
                currentHash = (currentHash + anotherHash) % newSize;
                ++j;
            }
            newMap[currentHash] = new Node(data);
        }
    }

    map = newMap;
    alloc = newSize;
}

Table::~Table() {
}

int main() {
    char c;
    string str;

    Table* table = new Table();

    while (cin >> c >> str) {
        bool result;

        switch (c) {
        case '+':
            result = table->Add(str);
            break;
        case '-':
            result = table->Remove(str);
            break;
        case '?':
            result = table->Has(str);
            break;
        default:
            result = false;
        }

        cout << ((result) ? "OK" : "FAIL") << "\n";
    }

    delete table;
    return 0;
}

