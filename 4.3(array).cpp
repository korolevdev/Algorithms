/**
Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью
динамического буфера.
**/
#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

class Stack {
public:
    Stack();
    ~Stack();

    void Resize();
    void Push(int value);
    int Pop();
private:
    int *data;
    size_t size;
    size_t top;
};

class Queue {
public:
    Queue();
    ~Queue();

    void Enqueue(int value);
    int Dequeue();
private:
    Stack *leftStack;
    Stack *rightStack;
};


Stack::Stack() {
    size = INIT_SIZE;
    data = (int*) malloc(size * sizeof(int));
    if (data == NULL) {
        exit(OUT_OF_MEMORY);
    }
    top = 0;
}

Stack::~Stack() {
    free(data);
}


void Stack::Resize() {
    size *= MULTIPLIER;
    data = (int*) realloc(data, size * sizeof(int));
    if (data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

void Stack::Push(int value) {
    if (top >= size) {
        Resize();
    }
    data[top] = value;
    top++;
}


int Stack::Pop() {
    if (top == 0) {
        return -1;
    }
    top--;
    return data[top];
}

Queue::Queue() {
    leftStack = new Stack;
    rightStack = new Stack;
}

Queue::~Queue() {
    delete leftStack;
    delete rightStack;
}

void Queue::Enqueue(int value) {
    leftStack->Push(value);
}

int Queue::Dequeue() {
    if (rightStack->top)
        return rightStack->Pop();
    else {
        if (leftStack->IsEmpty())
            return -1;
        else {
            while (leftStack->top)
                rightStack->Push(leftStack->Pop());
            return rightStack->Pop();
        }
    }
}

int main() {
    Queue *queue = new Queue;
    int n, oper, num, value;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &oper, &num);
        switch(oper) {
        case 2:
            value = queue->Dequeue();
            if (value != num) {
                printf("NO");
                delete queue;
                return 0;
            }
            break;
        case 3:
            queue->Enqueue(num);
            break;
        }
    }
    printf("YES");
    delete queue;
    return 0;
}
