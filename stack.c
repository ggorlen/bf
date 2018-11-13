#include <stdlib.h>
#include "stack.h"

void push(Stack **s, void *data) {
    Stack *top = malloc(sizeof(*top));
    top->data = data;
    top->next = *s;
    *s = top;
}

void *peek(Stack **s) {
    return *s ? (*s)->data : NULL;
}

void pop(Stack **s) {
    if (*s) {
        Stack *tmp = *s;
        *s = (*s)->next;
        free(tmp);
    }
}

void free_stack(Stack **s) {
    while (*s) {
        pop(s);
    }
}
