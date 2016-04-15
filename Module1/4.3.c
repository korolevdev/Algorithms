#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    struct Node *head;
    int size;
} Stack;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void push(Stack *stack, int value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = stack->head;
    stack->head = tmp;
    stack->size++;
}

int pop(Stack *stack) {
    Node* prev = NULL;
    int value;
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

void push_query(Stack *leftStack, int value) {
    push(leftStack, value);
}

int pop_query(Stack *leftStack, Stack *rightStack) {
    if (rightStack->size)
        return pop(rightStack);
    else {
        if (!leftStack->size)
            return -1;
        else {
            while (leftStack->size)
                push(rightStack, pop(leftStack));
            return pop(rightStack);
        }
    }
}

int main () {
    Stack *leftStack = malloc(sizeof(Stack));
    Stack *rightStack = malloc(sizeof(Stack));
    int n, oper, num, value;
    leftStack->size = 0;
    rightStack->size = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &oper, &num);
        switch(oper) {
        case 2:
            value = pop_query(leftStack, rightStack);
            if (value != num) {
                printf("NO");
                return 0;
            }
            break;
        case 3:
            push_query(leftStack, num);
            break;
        }
    }
    printf("YES");
    return 0;
}

