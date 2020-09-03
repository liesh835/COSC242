#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/**
 * mylib.c
 * @author Josh Casey, Shaun Liew, Thomas Hunt
 * @date September 15, 2019.
 * Library file for various functions
 */

/**
 * calls the malloc method to allocate memory for arrays
 * @param s the amount of memory blocks needing to be allocated
 * @return result, allocated memory.
 */
void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    /* skip to the start of the word */
    while(!isalnum(c = getc(stream)) && EOF != c)
        ;
    if(EOF == c){
        return EOF;
    } else if(--limit > 0){ /*reduct limitby 1 to allow for the \0*/
        *w++ = tolower(c);
    }
    while(--limit > 0){
        if(isalnum(c = getc(stream))){
            *w++ = tolower(c);
        }else if('\'' == c){
            limit++;
        } else{
            break;
        }
    }
    *w = '\0';
    return w - s;
}

/**
 * checks if a given number is a prime or not
 * returning true if it is or false if not
 * @param candidate the number to check whether a prime or not
 * @return 1 if prime 0 if not.
 */
int is_prime(int candidate){
    int i;
    for(i = 2; i < candidate; i++){
        if(candidate % i == 0){
            return 0;
        }
       
    }
    return 1;
}

/**
 * Finds the next prime number that is higher
 * than or equal to  the given number
 * @param the number to find the closest prime to
 * @return num the closest prime number equal or higher than given number
 */
int get_next_prime(int num){
    while(num >= 0){
        if(is_prime(num)){
            return num;
        }
        num++;
            
    }
    return 0;
}

