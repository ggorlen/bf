#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

#define LINE_LEN 5000

char *read(char *fname) {
    char line[LINE_LEN];
    size_t result_len = 0;
    size_t result_size = LINE_LEN;
    char *result = malloc(sizeof(*result) * LINE_LEN);

    if (!result) {
        fprintf(stderr, "%s: %d: malloc failure\n", __func__, __LINE__);
        exit(0);
    }

    result[0] = '\0';
    FILE *fin = fopen(fname, "r");

    if (!fin) {
        fprintf(stderr, "%s: %d: fopen error\n", __func__, __LINE__);
        exit(0);
    }

    while (!feof(fin) && fgets(line, LINE_LEN, fin)) {
        size_t actual = strlen(line);
        result_len += actual;

        // expand result array as needed
        while (result_len >= result_size) {
            result_size += LINE_LEN;
            char *tmp = realloc(result, result_len * sizeof(*tmp));

            if (tmp) {
                result = tmp;
            } 
            else {
                fprintf(stderr, "%s: %d: realloc failure\n", __func__, __LINE__);
                exit(0);
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
    char *result;

    if (argc == 3) {
        char *input = read(argv[2]);
        result = interpret(src, input);
        free(input);
    }
    else {
        result = interpret(src, "");
    }

    printf("%s\n", result);
    free(result);
    free(src);

    return 0;
}
