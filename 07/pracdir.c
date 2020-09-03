/** initialize all include and define statements
 * create the *emalloc function which takes size_t s as a parameter
   - where *result is void and allocates memory to parameter s
   - if null, print to stderr that memory allocation failed, free result and exit
   - return result
 * create print_array function which takes the char array, average and string length as parameters
   - where if length > 0
     - then if the length of the array[0](string) is greater than the average length
        - print the word to stdout
   - recursively call the print_array function
 * create the main function
    - initialize all variables
        - char array wordlist to store strings
        - char array to scan strings
        - int num_words to match number of strings to be considered
        - double average to store the average length
    - create a while loop where the max number of words is greater than num_words and scanf continues until there is no input to be considered, where the input is stored in word (char) array (up to 79 words).
       - allocate memory to wordlist[num_words] by multiplying length of string(word) by wordlist[0][0]
       - copy string (word) to wordlist[num_words]
       - increment num_words
    - for loop that adds length of each word to average
    - if num_words > 0
       - compute average length
       - print average length to stderr, in two decimal places
       - call print_array function sending it wordlist, average and num_words
    - for loop to free malloc of wordlist
    return EXIT_SUCCESS
       
       
