#include <stdio.h>
#include <stdlib.h>

void repeat(int *a, int n){
    int *temparray, i;

    temparray = malloc(n * sizeof temparray[0]);
    if(NULL == temparray){
        fprintf(stderr, "memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < n; i++){
        temparray[i] = 0;
    }

    for(i = 0; i < n; i++){
        temparray[a[i]]++;
    }

    for(i = 0; i < n; i++){
        if(temparray[i] > 1){
            printf("%d occurs %d times\n", i, temparray[i]);
        }
    }
    free(temparray);
}

int main(void) {

   int array_size = 0;
   int *my_array;
   int i = 0;

   printf("Enter the size of the array:\n");
   scanf("%d", &array_size);
   my_array = malloc(array_size * sizeof my_array[0]);
   
   if (NULL == my_array) {
       fprintf(stderr, "memory allocation failed!\n");
       return EXIT_FAILURE;
   }
   
   for (i = 0; i < array_size; i++) {
       my_array[i] = rand() % array_size;
   }
   
   printf("What’s in the array:\n");
   for (i = 0; i < array_size; i++) {
       printf("%d ", my_array[i]);
   }
   printf("\n");
   
   repeat(my_array, array_size);
   free(my_array);
   
   return EXIT_SUCCESS;
}
