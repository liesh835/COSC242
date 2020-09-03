#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Seletion Sort.
 * @author Shaun Liew.
 */

/** defines array capacity. */

#define ARRAY_MAX 30000

/**
 * Method for sorting integers in the array through selection.
 * @param a* the array to sort, n the size of the array.
 */

void selection_sort(int *a, int n){
    int p, i, smallInd, temp;

    for(p = 0; p < n - 1; p++){
        smallInd = p;
        
        for(i = p + 1; i <= n - 1; i++){
            if(a[i] < a[smallInd]){
                smallInd = i;
            }
        }

        temp = a[p];
        a[p] = a[smallInd];
        a[smallInd] = temp;
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
    selection_sort(my_array, count);
    end = clock();
    for(i = 0;i < count; i++){
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
