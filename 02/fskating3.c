#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 10

int main(void){
    int i = 0, linesRead = 0;
    int discard, n;
    double a, b, c, judge1Total = 0, judge2Total = 0, judge3Total = 0;;
    double judge1[ARRAY_SIZE], judge2[ARRAY_SIZE], judge3[ARRAY_SIZE];
    double mean1, mean2, mean3;
    double var1 = 0, var2 = 0, var3 = 0;
    double sd1 = 0, sd2 = 0, sd3 = 0;

    while(EOF !=  scanf("%d%lg%lg%lg",&n, &a, &b, &c)){
        discard = n;
        judge1[i] = a;
        judge2[i] = b;
        judge3[i] = c;
        judge1Total += judge1[i];
        judge2Total += judge2[i];
        judge3Total += judge3[i];
        
        i++;
    }

    linesRead = i;

    mean1 = judge1Total/linesRead;
    mean2 = judge2Total/linesRead;
    mean3 = judge3Total/linesRead;

    
    for(i = 0; i < linesRead; i++){
        var1 += pow((judge1[i] - mean1), 2);
        var2 += pow((judge2[i] - mean2), 2);
        var3 += pow((judge3[i] - mean3), 2);
    }

    sd1 = sqrt((var1/(linesRead - 1)));
    sd2 = sqrt((var2/(linesRead - 1)));
    sd3 = sqrt((var3/(linesRead - 1)));

    printf("Judge 1: Average = %1.1f\tStandard Deviation = %1.1f\n", mean1, sd1);
    printf("Judge 2: Average = %1.1f\tStandard Deviation = %1.1f\n", mean2, sd2);
    printf("Judge 3: Average = %1.1f\tStandard Deviation = %1.1f\n", mean3, sd3);
    
    return EXIT_SUCCESS;
}
        
                          

