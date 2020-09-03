#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Insertion Sort.
 * @author Shaun Liew.
 */

/** defines array capacity. */

#define ARRAY_MAX 10000
#define STRING_LEN 80

/**
 * Method for sorting integers in the array through insertion.
 * @param a* the array to sort, n the size of the array.
 */

void selection_sort(char **a, int n){
    int p, i, smallInd;
    char *temp;

    for(p = 0; p < n - 1; p++){
        smallInd = p;
        
        for(i = p + 1; i <= n - 1; i++){
            if(strcmp(a[i], a[smallInd]) < 0){
                smallInd = i;
            }
        }

        temp = a[p];
        a[p] = a[smallInd];
        a[smallInd] = temp;
    }
}

void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_MAX];
    int i, num_words = 0;

    while(num_words < ARRAY_MAX && 1 == scanf("%79s", word)){
        wordlist[num_words] = emalloc((strlen(word) + 1 ) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    selection_sort(wordlist, num_words);

    for(i = 0; i < num_words; i++){
        printf("%s\n", wordlist[i]);
    }

    for(i = 0; i < num_words; i++){
        free(wordlist[i]);
    }
    
    return EXIT_SUCCESS;
}
