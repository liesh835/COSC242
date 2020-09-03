#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>
#include <stdio.h>

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char *, int, FILE *);
extern int is_prime(int);
extern int get_next_prime(int num);

#endif
