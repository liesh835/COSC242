#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

/**
 * htable.c
 * @author Josh Casey, Shaun Liew, Thomas Hunt
 * @date September 15, 2019.
 * Create, modifies and searches a hashtable.
 */

struct htablerec{
    int capacity;
    int num_keys;
    int *frequencies;
    char **keys;
    int *stats;
    hashing_t method;
};

/**
 * Creates a step to employ a double hashing insertmethod
 * For a hashtable
 *
 * @param h the hashtable that data is being inserted into
 * @param i_key the linear hash key that is being modified for th double hash
 * @return int value that determines the next key of the hashtabel to insert in
 */
static unsigned int htable_step(htable h, unsigned int i_key){
    return 1 + (i_key % (h->capacity - 1));
}

/**
 * Converts a string to an integer
 * converted value used to determine where to insert a string into a hashtable
 * @param word the string to be converted
 * @return result the converted unsigned int value
 */
static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;
    while(*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Frees the allocated memory of a hashtable
 * @param h the hashtable with memory to be freed
 */
void htable_free(htable h){
       
    free(h->keys);
    free(h->frequencies);
    free(h->stats);
    free(h);
}

/**
 * Inserts strings into a hashtable using either  linear probing
 * or double hashing depedning on predefeined method
 * @param h the hashtable to insert words into
 * @param str the word to be inserted
 */
int htable_insert(htable h, char *str){
    int count;
    unsigned int str_int;
    unsigned int hash;
    int num_collisions = 0;
    int step;
    /*if double is specified as method*/
    /* uses double hashing*/
    if(h->method == DOUBLE_H){
            
        str_int = htable_word_to_int(str);
        hash = str_int % h->capacity;
        step = htable_step(h, str_int);
        count = 0;
        while(count < h->capacity){
            /*  if((int)hash >= h->capacity){
                hash = 0;
                }*/
            if(h->keys[hash] == NULL){
                h->keys[hash] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
                strcpy(h->keys[hash], str);
                h->frequencies[hash]++;
                h->stats[h->num_keys] = num_collisions;
                h->num_keys++;
                    
                return 1;
            }
            else if(strcmp(h->keys[hash], str) == 0){
                h->frequencies[hash]++;
                return h->frequencies[hash];
            }
            count++;
            hash = (hash + step) % h->capacity;
            num_collisions++;
                
            
        }
           
        return 0;
    }
    /*linear probing done by default*/
    else{
        str_int = htable_word_to_int(str);
        hash = str_int % h->capacity;
        count = 0;
        while(count < h->capacity){
            /* if((int)hash >= h->capacity){
               hash = 0;
               }*/
            if(h->keys[hash] == NULL){
                h->keys[hash] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
                strcpy(h->keys[hash], str);
                h->frequencies[hash]++;
                h->stats[h->num_keys] = num_collisions;
                h->num_keys++;
                return 1;
            }
            else if(strcmp(h->keys[hash], str) == 0){
                h->frequencies[hash]++;
                return h->frequencies[hash];
            }
            count++;
            hash = (hash + 1) % h->capacity;
            num_collisions++;
            
        }
            
        return 0;
    }
}
/**
 * Creates a new hashtable initialising the variables of the struct
 * to their defaults and allocation memory as needed.
 * @param capacity the amount of strings that can be stored in the hashtable
 * @param method the hashing method to use when inserting data the htable
 * @return result the newly created hashtable struct
 */
htable htable_new(int capacity, hashing_t method){
    int i;
    htable result = emalloc(sizeof * result);
    result->method = method;
    result->capacity = capacity;
    result->num_keys = 0;
    result->frequencies = emalloc(capacity * sizeof result->frequencies[0]);
    result->keys = emalloc(capacity * sizeof result->keys[0]);
    result->stats = emalloc(capacity * sizeof result->stats[0]);
    for(i = 0; i < capacity; i++){
        result->keys[i] = NULL;
        result->frequencies[i] = 0;
        result->stats[i] = 0;
    }
    return result;
}

/**
 * prints each word stored in the hashtable and the frequency
 * of each word
 * @param h the hashtable with the values to print
 * @param f a function that is passed that determines how to print the values
 */
void htable_print(htable h, void (*f)(int, char *)){
    int i;
    for(i = 0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            f(h->frequencies[i], h->keys[i]);
        }
    }
}

/**
 * Prints out the hashtable, showing the postion
 * frequency and stats of each word stored
 * @param h the hashtable to print
 */
void htable_print_entire_table(htable h) {
    int i = 0;
    printf("%5s %5s %5s   %s\n", "Pos", "Freq", "Stats", "Word");
    printf("----------------------------------------\n");
    for (i = 0; i < h->capacity; i++) {
        if (h->keys != NULL) {
            printf("%5d %5d %5d   %s\n", i, h->frequencies[i], h->stats[i], h->keys[i]);
        } else {
            printf("%5d %5d %5d   %s\n", i, h->frequencies[i], h->stats[i], "");
        }
    }
}

/**
 * Searches a hashtable and checks whether a given word is present
 * in it, if it is returns the frequency of the word in the hashtable
 * if it's not returns 0
 * @param h the hashtable to search inside
 * @param str the word to search for
 * @return 0 if the word is not in the hashtable
 * @return h->frequencies[hash] the frequency of the searched for word
 */
int htable_search(htable h, char *str){
    int collision = 0;
    unsigned int str_int = htable_word_to_int(str);
    unsigned int hash = str_int % h->capacity;
    unsigned int step = htable_step(h, str_int);
    /*if the probing method is double hashing*/
    if(h->method == DOUBLE_H){
        while(h->keys[hash] != NULL && strcmp(h->keys[hash], str) != 0 && collision < h->capacity){
            hash += step;
            collision++;
        }
        if(collision == h->capacity){
            return 0;
        }
        else{
            return h->frequencies[hash];
        }
    }
    /*linear by default*/
    else{
        while(h->keys[hash] != NULL && strcmp(h->keys[hash], str) != 0 && collision < h->capacity){
            hash++;
            collision++;
        }
        if(collision == h->capacity){
            return 0;
        }
        else{
            return h->frequencies[hash];
        }
    }
}
      

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "------------------------------------------------------\n\n");
}
