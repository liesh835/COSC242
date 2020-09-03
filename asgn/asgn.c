#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "mylib.h"
#include "htable.h"

/**
 * asgn.c
 * @author Josh Casey, Shaun Liew, Thomas Hunt
 * @date September 15, 2019.
 * Main file for htable
 */


/**
 * Prints out instructions for how to operate the program. Provides a list of
 * the command line arguments that work with the program and provides a
 * description of what each of them do.
 */
void helpMessage() {
    printf("Usage: ./asgn [OPTION]... <STDIN>\n\n");
    printf("Perform various operations using a hash table. ");
    printf("By default word are\n");
    printf("read from stdin and added to the hash table, ");
    printf("before being printed out\n");
    printf("alongside their frequencies to stdout.\n\n");

    printf("-c FILENAME  Check spelling of words in FILENAME using words\n");
    printf("\t     from stdin as dictionary. Print unknown words to\n");
    printf("\t     stdout, timing info & count to stderr (ignore -p)\n");
    printf("-d \t     Use double hasing (linear probing is the default)\n");
    printf("-e \t     Display entire contents of hash table on stderr\n");
    printf("-p \t     Print stats info instead of frequencies & words\n");
    printf("-s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
    printf("-t TABLESIZE Use the first prime >= TABLESIZE as htable size\n\n");
    printf("-h \t     Display this message\n");
}

/**
 * Prints a frequency int values and a word
 * is passed to htable_print and used to print
 * the words and frequncy of each word currently
 * in the hashtable
 *
 * @param freq the number of times a single word was inserted into the hashtable
 * @param word a word stored in a hashtable to be printed
 */
static void print_info(int freq, char *word){
    printf("%-4d %s\n", freq, word);
}

/**
 * By default creates a hashtable datastructure
 * reads strings from Stdin and inserts them into the hashtable
 * then prints each stored string and the frequecny of which the
 * word was inserted.
 * The program also accepts several commandline arguemnts
 * each different command line changes the behaviour of the program
 * To see a list of all accepted arguments and descriptions of thier
 * behaviour run the program with -h as an argument
 * @param argc argument count
 * @param argv argument array
 */
int main(int argc, char **argv) {
    int size = 113;
    hashing_t type = LINEAR_P;
    htable h;
    const char *optstring = "c:deps:t:h";
    char option;
    char word[256];  

    clock_t start, stop;
    double searchTime;
    double fillTime;

    FILE *infile = NULL;
    int spellCheck = 0;
    int printTable = 0;
    int printStats = 0;
   
    int unknown = 0;
    int max_snap = 10;   

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            
            case 'c':
                if (NULL == (infile = fopen(optarg, "r"))) {
                    fprintf(stderr, "%s: can't find file %s\n", argv[0],argv[1]);
                    return EXIT_FAILURE;
                }
                spellCheck = 1;
                break;
            case 'd':
                type = DOUBLE_H;
                break;
            case 'e':
                printTable = 1;
                break;
            case 'p':
                printStats = 1;
                break;
            case 's':
                
                max_snap = atoi(optarg);
                break;
            case 't':
                size = get_next_prime(atoi(optarg));/* converts char* to int*/
                break;
            case 'h':
                helpMessage();
                break;
            default:
                helpMessage();
                break;
        }
    }

    /* initalises an empty hashtable*/
    h = htable_new(size, type);

    /* reads from stdin and inserts into hashtable*/
    /* then searches hashtable for words in given file*/
    /* prints all words in file not in the hashtable*/
    /* and prints insert and search times*/
    
    if (spellCheck == 1) {
        start = clock();
        while(getword(word, sizeof word, stdin) != EOF){
            htable_insert(h, word);
        }
        stop = clock();
        fillTime = ((stop-start)/(double)CLOCKS_PER_SEC);
        start = clock();
        while (getword(word, sizeof word, infile) != EOF) {
            if (htable_search(h, word) == 0) {
                printf("%s\n", word);
                unknown++;
            }
        }
        stop = clock();
        searchTime = ((stop-start)/(double)CLOCKS_PER_SEC);
        fprintf(stderr, "Fill time: %2.6f\n", fillTime);
        fprintf(stderr, "Search time: %2.6f\n", searchTime);
        fprintf(stderr, "Unknown words: %d\n", unknown);
        htable_free(h);
        return EXIT_SUCCESS;
    }

    /* inserts words from stdin into hashtable*/
    while(getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }

    /* prints the contents of the hashtable*/
    if (printTable == 1) {
        htable_print_entire_table(h);
    }

    
    /* prints several stats about the current hashtable*/
    if(printStats == 1){
        if(max_snap > 0){
            htable_print_stats(h, stdout, max_snap);
            htable_free(h);
            return EXIT_SUCCESS;
        }
        
    }
    
    /*prints each word in the hashtable and their frequencies*/    
    htable_print(h, print_info);
    htable_free(h);
   
    return EXIT_SUCCESS;
                             
} 
