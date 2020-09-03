#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s){
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_SUCCESS);
    }
    return result;
}

void *erealloc(void *p, size_t s){
    p = realloc(p, s);
    if(p == NULL){
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_SUCCESS);
    }
    return p;
}

void selection_sort(int *a, int n){
    int i, j, smallInd, x, temp;

    for(i = 0; i < n - 1; i++){
        smallInd = i;
        
        for(j = i + 1; j < n; j++){
            if(a[j] < a[smallInd]){
                smallInd = j;
            }
        }

        temp = a[smallInd];
        a[smallInd] = a[i];
        a[i] = temp;

        if(i == n/2 - 1){
            for(x = 0; x < n; x++){
                fprintf(stderr, "%d\n", a[x]);
            }
        }
    }
}


flexarray flexarray_new(){
    flexarray f = emalloc (sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(f->capacity * sizeof f->items[0]);
    return f;
}

void flexarray_append(flexarray f, int num){
    if(f->itemcount == f->capacity){
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f){
    int i;
    for(i = 0; i < f->itemcount; i++){
        printf("%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    selection_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}
                       
