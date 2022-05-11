#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct ali {
     char *name;
     int (*func)(void);
} alias;
alias aliases[] = {
     {"name", function},
     {NULL, NULL}
};
typedef struct bin{
     char *name;
     int (*func)(void);
} builtin;
builtin builtins[] = {
     {"exit", exit_function},
     {"env", env_function},
     {NULL, NULL}
};

int _strlen(char *s);
char *_strncat(char *dest, char *src, int n);
char *_strdunp(char *lo);

#endif /* MAIN_H */
