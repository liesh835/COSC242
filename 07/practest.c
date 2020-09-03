#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 80

void *emalloc(size_t s){
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr, "Failed memory allocation\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_array(char **a, double av, int n){
    if(n > 0){
        if(strlen(a[0]) > av){
            printf("%s\n", a[0]);
        }
        print_array(a+1,av,n - 1);
    }
}

int main(void){
    char word[MAX_LENGTH];
    char *wordlist[MAX_WORDS];
    double average = 0.0;
    int i, num_words = 0;

    while(num_words < MAX_WORDS && 1 == scanf("%79s", word)){
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    for(i = 0; i < num_words; i++){
        average += strlen(wordlist[i]);
    }

    if(num_words > 0){
        average /= num_words;
        fprintf(stderr, "%.2f\n", average);
        print_array(wordlist, average, num_words);
    }

    for(i = 0; i < num_words; i++){
        free(wordlist[i]);
    }

    return EXIT_SUCCESS;
}
                    
                                                            
