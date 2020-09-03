#include <stdlib.h>
#include <stdio.h>

int main(void){
    double s1, s2, s3, high_score = 0.0, result;
    int id, winner = 0;

    while(4 == scanf("%d%lg%lg%lg", &id, &s1, &s2, &s3)){
        if(s1 < s2 && s1 < s3){
            result = (s2 + s3)/2;
        }else if(s2 < s3 && s2 < s1){
            result = (s1 + s3)/2;
        }else{
            result = (s1 + s2)/2;
        }

        if(result > high_score){
            high_score = result;
            winner = id;
        }
    }

    printf("%d\n", winner);

    return EXIT_SUCCESS;
}
