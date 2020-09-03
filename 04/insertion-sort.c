#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Insertion Sort.
 * @author Shaun Liew.
 */

/** defines array capacity. */

#define ARRAY_MAX 30000

/**
 * Method for sorting integers in the array through insertion.
 * @param a* the array to sort, n the size of the array.
 */

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

/**
 * main method for timing and user input.
 */

int main(void){
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while(count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for(i = 0;i < count; i++){
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
