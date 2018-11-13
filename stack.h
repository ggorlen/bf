#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack {
    void *data;
    struct Stack *next;
} Stack;

void push(Stack **s, void *data);
void *peek(Stack **s);
void pop(Stack **s);
void free_stack(Stack **s);

#endif
