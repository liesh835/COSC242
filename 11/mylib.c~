#include <stdio.h> 
#include <stdlib.h> 
#include "mylib.h"

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if(result == NULL){
        fprintf(stderr, "Memory reallocation failed\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    return result;
}
