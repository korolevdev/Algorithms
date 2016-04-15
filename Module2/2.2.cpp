/**
Для сложения чисел используется старый компьютер. Время, затрачиваемое 
на нахождение суммы двух чисел равно их сумме.

Требуется написать программу, которая определяет минимальное время, достаточное для
вычисления суммы заданного набора чисел.
**/
#include <iostream>
#include <algorithm>

using namespace std;

class Heap {
public:
    Heap(int);
    ~Heap();

    int GetSize();
    int ExtractMin();
    void Insert(int);
    int GetTop();
private:
    void siftUp(int);
    void siftDown(int);
    void swap(int, int);
    int *arr;
    int size;
};

Heap::Heap(int heapSize): size(0) {
    arr = new int[heapSize];
}

Heap::~Heap() {
    delete[] arr;
}

int Heap::GetSize() {
    return size;
}

int Heap::GetTop() {
    int temp = arr[0];
    swap(0, --size);
    siftDown(0);
    return temp;
}

void Heap::swap(int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void Heap::siftUp(int i) {
    while (arr[i] < arr[(i - 1) / 2]) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void Heap::Insert(int value) {
    arr[size++] = value;
    siftUp(size - 1);
}

void Heap::siftDown(int i) {
    while (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < size && arr[right] < arr[left])
            j = right;
        if (arr[i] <= arr[j])
            break;
        swap(i, j);
        i = j;
    }
}

int calc(Heap *heap) {
    int time = 0;
    int sum;
    while ( heap->GetSize() > 1 ) {
        sum = heap->GetTop();
        sum += heap->GetTop();
        heap->Insert(sum);
        time += sum;
    }
    return time;
}

int main() {
    int size, elm;
    cin >> size;

    Heap *heap = new Heap(size);

    for (int i = 0; i < size; ++i) {
        cin >> elm;
        heap->Insert(elm);
    }

    cout << calc(heap);

    delete heap;

    return 0;
}


