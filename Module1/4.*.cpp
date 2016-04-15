#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

/**
Персистентная очередь
**/

using namespace std;

class Stack {
public:
    Stack();
    ~Stack();

    void Resize();
    void Push(int value);
    int Pop();
    int getTop();

private:
    int *data;
    size_t size;
    size_t top;
};

class Query {
public:
    Query();
    ~Query();

    void Enqueue(int value);
    int Dequeue();
    void CheckRecopy();
    void CheckNormal();
    bool Empty();
    void AdditionalOperations();

private:
    Stack *L;
    Stack *Ll;
    Stack *R;
    Stack *Rc;
    Stack *Rcl;
    Stack *S;
    bool recopy = false;
    bool copied = true;
    int toCopy = 0;
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

int Stack::getTop() {
    return top;
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

Query::Query() {
    L = new Stack();
    Ll = new Stack();
    R = new Stack();
    Rc = new Stack();
    Rcl = new Stack();
    S = new Stack();
}

Query::~Query() {
    delete L;
    delete Ll;
    delete R;
    delete Rc;
    delete Rcl;
    delete S;
}

bool Query::Empty() {
    return (!recopy && R->getTop() == 0);
}

void Query::AdditionalOperations() {
    // Нам достаточно 3 операций на вызов
    int toDo = 3;
    // Пытаемся перекопировать R в S
    while (!copied && toDo > 0 && R->getTop() > 0) {
        S->Push(R->Pop());
        toDo--;
    }
    // Пытаемся перекопировать L в R и Rc'
    while (toDo > 0 && L->getTop() > 0) {
        copied = true;
        int x = L->Pop();
        R->Push(x);
        Rcl->Push(x);
        toDo--;
    }
    // Пытаемся перекопировать S в R и Rc' с учетом toCopy
    while (toDo > 0 && S->getTop() > 0) {
        int x = S->Pop();
        if (toCopy > 0) {
            R->Push(x);
            Rcl->Push(x);
            toCopy--;
        }
        toDo--;
    }
    // Если все скопировано, то меняем роли L, L' и Rc, Rc'
    if (S->getTop() == 0) {
        swap(L, Ll);
        swap(Rc, Rcl);
    }
}

void Query::CheckNormal() {
    AdditionalOperations();
    // Если мы не все перекопировали, то у нас не пуст стек S
    if (S->getTop() != 0)
        recopy = true;
    else
        recopy = false;
    //recopy = (S->size != 0);
}

void Query::CheckRecopy() {
    if (L->getTop() > R->getTop())
        recopy = true;
    else
        recopy = false;
    //recopy = L->size > R->size;
    if (recopy) {
        toCopy = R->getTop();
        copied = false;
        CheckNormal();
    }
}

void Query::Enqueue(int x) {
    if (!recopy) {
        L->Push(x);
        if (Rcl->getTop() > 0)
            Rcl->Pop();
        CheckRecopy();
    } else {
        Ll->Push(x);
        CheckNormal();
    }
}

int Query::Dequeue() {
    if (!recopy) {
        int tmp = R->Pop();
        Rc->Pop();
        if (Rcl->getTop() > 0)
            Rcl->Pop();
        CheckRecopy();
        return tmp;
    } else {
        int tmp = Rc->Pop();
        if (toCopy > 0)
            toCopy--;
        else {
            R->Pop();
            Rcl->Pop();
        }
        CheckNormal();
        return tmp;
    }
}

int main() {
    Query *query = new Query();

    int n, oper, num, value;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &oper, &num);
        switch(oper) {
        case 2:
            value = query->Dequeue();
            if (value != num) {
                delete query;
                printf("NO");
                return 0;
            }
            break;
        case 3:
            query->Enqueue(num);
            break;
        }
    }
    delete query;
    printf("YES");
}
