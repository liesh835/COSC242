#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i = 0;
    int f = 0;
    int g = 1;
    int temp = 0;

    for(i = 1; i < 41; i++){
        printf("%d, ", g);
        temp = g;
        g += f;
        f = temp;

        if(i % 5 == 0){
            printf("\n");
        }
        
    }

    return EXIT_SUCCESS;
}
