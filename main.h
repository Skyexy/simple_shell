#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUFFER_LEN 1024

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

int check(char *s);
void comma(char *user_input);
int divd(char *user_input);
int ali(char **argv);
int exv(char **argv);
void execute(char** argv);
char *_getpath(void);
int cd(char **argv);
int env(char **argv);
int _exi(char **argv);
int comp(char **argv, char *sig);

#endif /* MAIN_H */
