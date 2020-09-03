#include <stdio.h>
#include <stdlib.h>

int main(void){
    double s1, s2, s3, average;

    printf("Judges' First Score: ");
    scanf("%lg", &s1);
    printf("Judges' Second Score: ");
    scanf("%lg", &s2);
    printf("Judges' Third Score: ");
    scanf("%lg", &s3);

    if(s1 >= 0 && s2 >= 0 && s3 >= 0){ 

        if(s1 >= 6.0 || s2 >= 6.0 || s3 >= 6.0){
            printf("Scores must be a maximum of 6.0\n");
            
        }else if(s1 < s2 && s1 < s3){
            average = (s2 + s3)/2;
            printf("The Average Score: %2.2f\n", average);
        
        }else if(s2 < s1 && s2 < s3){
            average = (s1 + s3)/2;
            printf("The Average Score: %2.2f\n", average);
        
        }else{        
            average = (s1 + s2)/2;
            printf("The Average Score: %2.2f\n", average);
        }
    }

        return EXIT_SUCCESS;
    }
