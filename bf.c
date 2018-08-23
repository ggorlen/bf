#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

#define LINE_LEN 5000

char *read(char *fname) {
    char line[LINE_LEN];
    size_t result_len = 0;
    size_t result_size = LINE_LEN;
    char *result = malloc(sizeof(result) * LINE_LEN);

    if (!result) {
        puts("malloc failure");
        exit(0);
    }

    result[0] = '\0';
    FILE *fin = fopen(fname, "r");

    if (!fin) {
        puts("fopen error"); 
        exit(0); 
    }

    while (!feof(fin) && fgets(line, LINE_LEN, fin)) {
        size_t actual = strlen(line);
        result_len += actual;

        // expand result array as needed
        while (result_len >= result_size) {
            result_size += LINE_LEN;
            char *tmp = realloc(result, result_len * sizeof(tmp));

            if (tmp) {
                result = tmp;
            } 
            else {
                puts("realloc failure");
            }
        }

        strncat(result, line, actual);
    }

    fclose(fin);
    return result;
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        puts("usage: bf.exe sourcefile [inputfile]");
        exit(0);
    }

    char *src = read(argv[1]);

    if (argc == 3) {
        char *input = read(argv[2]);
        interpret(src, input);
        free(input);
    }
    else {
        interpret(src, "");
    }

    free(src);
    return 0;
}
