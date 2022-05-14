#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct aliases {
char *alias_name;
char *real_name;
} alias;

alias my_aliases[] = {
{"ls", "ls --color=auto"},
{"ll", "ls -alF"},
{"la", "ls -A"},
{NULL, NULL},
};


typedef struct my_builtins
{
char *name;
int (*func)(char **);
} my_builtins;

my_builtins builtins[] = {
     {"exit", &_exi},
     {"env", &env},
     {"cd", &cd},
     {NULL, NULL},
};

int _strlen(char *s);
char *_strncat(char *dest, char *src, int n);
char *_strdunp(char *lo);

#endif /* MAIN_H */
