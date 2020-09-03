#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    double a, b ,c;
    int leader = 0;
    double largest_score = 0.0;


    do{
        scanf("%d%lg%lg%lg", &n, &a, &b, &c);
        
        if(a > largest_score){
            largest_score = a;
            leader = n;
        }
            
        if(b > largest_score){
            largest_score = b;
            leader = n;
        }
        
        if(c > largest_score){
            largest_score = c;
            leader = n;
        }
        
    }while(EOF !=  scanf("%d%lg%lg%lg", &n, &a, &b, &c));

    printf("The Winner is %d with a highscore of %1.2f", leader, largest_score);
    return EXIT_SUCCESS;
}

        
