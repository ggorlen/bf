#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define CELL_SIZE 256
#define TAPE_SIZE 30000

void interpret(char *src, char *input) {
    int tape_ptr = 0;
    int input_ptr = 0;
    int src_ptr = 0;
    int src_len = strlen(src);
    int input_len = strlen(input);
    int tape[TAPE_SIZE] = {0};
    int brackets[src_len];
    memset(brackets, -1, sizeof(brackets));
    Stack *s = NULL;
    
    for (int i = 0; i < src_len; i++) {
        if (src[i] == '[') {
            push(&s, i);
        }
        else if (src[i] == ']') {
            brackets[i] = peek(s);
            brackets[peek(s)] = i;
            pop(&s);
        }
    }

    for (; tape_ptr < TAPE_SIZE && src_ptr < src_len; src_ptr++) {
        switch (src[src_ptr]) {
        case '>': 
            tape_ptr++; 
            break;
        case '<': 
            tape_ptr--; 
            break;
        case '+': 
            tape[tape_ptr] = (1 + tape[tape_ptr]) % CELL_SIZE;
            break;
        case '-': 
            tape[tape_ptr] = tape[tape_ptr] == 0 ? 
                CELL_SIZE - 1 : tape[tape_ptr] - 1;
            break;
        case ',':
            if (input_ptr < input_len) {
                tape[tape_ptr] = input[input_ptr++];
            }

            break;
        case '.':
            printf("%c", tape[tape_ptr]);
            break;
        case '[':
            if (tape[tape_ptr] == 0) { 
                src_ptr = brackets[src_ptr];
            }

            break;
        case ']':
            if (tape[tape_ptr] > 0) {
                src_ptr = brackets[src_ptr];
            }

            break;
        }
    }
}
