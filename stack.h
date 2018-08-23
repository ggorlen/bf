#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int data;
    struct Stack *next;
} Stack;

Stack *newNode(int data);
void push(Stack **s, int data);
int peek(Stack *s);
void pop(Stack **s);
void freeStack(Stack **s);

#endif
