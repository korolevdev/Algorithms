/**
Дана последовательность ​прямоугольников различной ширины и высоты (w​​, h). Прямоугольники  расположены, начиная с точки (0, 0),
на оси ОХ вплотную друг за другом (вправо). Требуется найти ​​
M площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой
фигуры.
**/
#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    int x;
    int y;
} Data;

typedef struct Stack {
    struct Node *head;
    int size;
} Stack;

typedef struct Node {
    Data value;
    struct Node* next;
} Node;

void push(Stack *stack, int x, int y) {
    Data value;
    value.x = x;
    value.y = y;
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = stack->head;
    stack->head = tmp;
    stack->size++;
}

Data pop(Stack *stack) {
    Node* prev = NULL;
    Data value;
    if (stack->head == NULL) {
        exit(-1);
    }
    prev = stack->head;
    value = prev->value;
    stack->head = stack->head->next;
    stack->size--;
    free(prev);
    return value;
}

void delete_stack(Stack *stack) {
    while (stack->head) {
        Node* temp = stack->head->next;
        free(stack->head);
        stack->head = temp;
    }
    free(stack);
}

int calc(Stack *stack, int n) {
    int x1 = -1, y1 = -1, max = 0;
    int x, y;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x, &y);
        if (y1 == -1) {
            x1 = x;
            y1 = y;
            max = x1*y1;
            continue;
        }
        if (y > y1) {
            push(stack, x1, y1);
            x1 = x;
            y1 = y;
            if (x1*y1 > max)
                max = x1*y1;
        } else {
            int sum = 0;
            push(stack, x1, y1);
            x1 = x;
            y1 = y;
            while (stack->size > 0) {
                Data value = pop(stack);
                if (value.y >= y1) {
                    x1 += value.x;
                    sum += value.x;
                    if (sum*value.y > max)
                        max = sum*value.y;
                    if (x1*y1 > max)
                        max = x1*y1;
                } else {
                    push(stack, value.x, value.y);
                    break;
                }
            }
            if (x1*y1 > max)
                max = x1*y1;
        }
    }
    while (stack->size > 0) {
        Data value = pop(stack);
        x1 += value.x;
        y1 = value.y;
        if (x1*y1 > max)
            max = x1*y1;
    }
    return max;
}

int main() {
    int n;
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->size = 0;
    scanf("%d", &n);
    printf("%d", calc(stack, n));
    delete_stack(stack);
    return 0;
}
