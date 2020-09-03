#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"


static void array_print(int *a, int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

void insertion_sort(int *a, int n){
    int p, key, i;
    for(p = 1; p < n; p++){
        key = a[p];
        i = p - 1;
        while(i >= 0 && a[i] > key){
            a[i + 1] = a[i];
            i -= 1;
        }
        a[i + 1] = key;
    }    
}


int main(void) {
    int capacity = 2, itemcount = 0, item = 0;
    int*my_array = emalloc(capacity * sizeof my_array[0]);

 
    while(1 == scanf("%d", &item)){
        if(itemcount == capacity){
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
        }
        my_array[itemcount++] = item;
    }

    insertion_sort(my_array, itemcount);
    array_print(my_array, itemcount);
    free(my_array);

    return EXIT_SUCCESS;
}
