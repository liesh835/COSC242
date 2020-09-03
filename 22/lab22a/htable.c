#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec{
    int capacity;
    int num_keys;
    char **keys;
};
static unsigned int htable_hash(htable h, unsigned int i_key){
    return i_key % h->capacity;
}

static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;
    while(*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}


void htable_free(htable h){
    int i = 0;

    for(i = 0; i < h->capacity; i++){
    free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}


int htable_insert(htable h, char *str){
    int count;
    unsigned int str_int;
    unsigned int hash; 
 
    str_int = htable_word_to_int(str);
    hash = htable_hash(h, str_int);
    count = 0;
    
    while(count < h->capacity){
        if(h->keys[hash] == NULL){
            h->keys[hash] = erealloc(h->keys[hash],(strlen(str) + 1) * sizeof str[0]);
            strcpy(h->keys[hash], str);
            h->num_keys++;
            return 1;
        }else if(strcmp(h->keys[hash], str) == 0){
            return 1;
        }
       
        count++;
        hash = (hash + 1) % h->capacity;
            
    }
            
    return 0;
}


htable htable_new(int capacity){
    int i;
    htable result = emalloc(sizeof * result);
    
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    
    for(i = 0; i < capacity; i++){
        result->keys[i] = NULL;
    }
    return result;
}


void htable_print(htable h, FILE *stream) {
    int i = 0;

    for(i = 0; i < h->capacity; i++){
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}

