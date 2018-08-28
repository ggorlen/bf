#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "stack.h"

Stack *newNode(int data) {
    Stack *node = malloc(sizeof(node));
    assert(node);
    node->data = data;
    node->next = NULL;
    return node;
}

void push(Stack **s, int data) {
    Stack *top = newNode(data);
    top->next = *s;
    *s = top;
}

int peek(Stack *s) {
    return s ? s->data : -INFINITY;
}

void pop(Stack **s) {
    if (*s) {
        Stack *tmp = *s;
        *s = (*s)->next;
        free(tmp);
    }
}

void freeStack(Stack **s) {
    while (*s) {
        pop(s);
    }
}
