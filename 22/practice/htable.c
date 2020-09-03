#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
    return i_key % h->capacity;
}

htable htable_new(int capacity){
    int i;

    htable result = emalloc(sizeof * result);

    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);

    for(i=0;i < capacity; i++){
        result->keys[i] = NULL;
    }

    return result;
}

void htable_free(htable h){
    int i;
    
    for(i = 0; i < h->capacity; i++){
        free(h->keys[i]);
    }
    
    free(h->keys);
    free(h);
}

int htable_insert(htable h, char *key) {
    /**
     * initialize variables count, str_int to store htable word to int, hash to store str_int in htable hash.
     * as count is less than the capacity
     * IF at index hash, keys is null
     * reallocate memory to h->key[hash], length of given string + 1 times the sizeof the char array
     * copy string to h->keys[hash]
     * increment num_keys
     * return 1 to keep loop going
     * else if comparing hash index and string returns 0, return 1
     * }
     * increment count
     * make hash = hash + 1 % capacity
     * return 0
     */

    int count;
    unsigned int str_int;
    unsigned int hash;

    str_int = htable_word_to_int(key);
    hash = htable_hash(h, str_int);
    count = 0;

    while(count < h->capacity){
        if(h->keys[hash] == NULL){
            h->keys[hash] = erealloc(h->keys[hash],(strlen(key) + 1) * sizeof key[0]);
            strcpy(h->keys[hash], key);
            h->num_keys++;
            return 1;
        }else if(strcmp(h->keys[hash], key) == 0){
            return 1;
        }
        count++;
        hash = (hash + 1) % h->capacity;
    }
    return 0;
            
}

void htable_print(htable h, FILE *stream) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
