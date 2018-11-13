#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define CELL_SIZE 256
#define TAPE_SIZE 30000

char *interpret(char *src, char *input) {
    int top, i;
    int tape_ptr = 0;
    int input_ptr = 0;
    int src_ptr = 0;
    int src_len = strlen(src);
    int input_len = strlen(input);
    int tape[TAPE_SIZE] = {0};
    int brackets[src_len];
    int i_refs[src_len];
    char *result = malloc(sizeof(*result) * src_len);
    int result_len = 0;
    int result_capacity = src_len - 1;
    Stack *s = NULL;
    
    for (i = 0; i < src_len; i++) {
        if (src[i] == '[') {
            i_refs[i] = i;
            push(&s, &i_refs[i]);
        }
        else if (src[i] == ']') {
            top = *(int *)peek(&s);
            brackets[i] = top; 
            brackets[top] = i;
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
            if (result_len >= result_capacity) {
                result_capacity *= 2;
                char *tmp = realloc(result, result_capacity * sizeof(*tmp));
     
                if (tmp) {
                    result = tmp;
                } 
                else {
                    fprintf(stderr, "%s: %d: realloc failure\n", __func__, __LINE__);
                    exit(0);
                }
            }
     
            result[result_len++] = tape[tape_ptr];
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

    result[result_len] = '\0';
    return result;
}
