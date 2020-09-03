/**
 * 1. reading from scanf (stdin) of a max of 100 words - store in array (main)
 * 2. create an emalloc function to allocate memory (void *emalloc(size_t s))
 * 3. calculate average word length - for loop that adds strlen(a[i]) to total, then dividing by number of words (main)
 * 4. create a print (stdout) function which prints words that are greater than average length, recursively void print_array(int *a, int a)
 * 5. print (stderr) the average word length to two decimal places (main)
 * 6. deallocate all allocated memory (free()) (main)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory allocaion failed!\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_array(char **a, double av, int n){
    if(n > 0){
        if(strlen(a[0]) > av){
            fprintf(stdout, "%s\n", a[0]);
        }
        print_array(a + 1, av, n - 1);
    }
}

int main(void){
    
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words = 0, i;
    double average = 0.0;

    while(num_words < ARRAY_LEN && 1 == scanf("%79s", word)){
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    for(i = 0; i < num_words; i++){
        average += strlen(wordlist[i]);
    }

    if(num_words > 0){
        average = average/num_words;
        fprintf(stderr, "%.2f\n", average);
        print_array(wordlist, average, num_words);    
    }
    
    for(i = 0; i < num_words; i++){
        free(wordlist[i]);
    }
    
    return EXIT_SUCCESS;
}

    
    
        
