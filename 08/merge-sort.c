#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARRAY_MAX 100000

void merge(int *array, int *workspace, int len){
    int left = 0, right = len/2, i = 0;
    while(left < len/2 && right < len){

        if(array[left] < array[right]){
            workspace[i++] = array[left++];
        }else{
            workspace[i++] = array[right++];
        }
    }

    while(left < len/2){
        workspace[i++] = array[left++];
    }

    while(right < len){
        workspace[i++] = array[right++];
    }
}
            
void merge_sort(int *a, int *w, int n){
    int mid = n/2, i = 0;
    
    if(n < 2){
        return;
    }else{
        merge_sort(a, w, mid);
        merge_sort(a + mid, w, (n - mid));
        merge(a, w, n);


        for(i = 0; i < n; i++){
            a[i] = w[i];
        }
    }
}
/**
 * main method for timing and user input.
 */

int main(void){
    int my_array[ARRAY_MAX], w_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while(count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    
    start = clock();
    merge_sort(my_array, w_array, count);
    end = clock();
    
    for(i = 0; i < count; i++){
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
