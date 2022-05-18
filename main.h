#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUFFER_LEN 1024

typedef struct aliases
{
char *alias_name;
char *real_name;
} alias;
typedef struct my_builtins
{
char *name;
int (*func)(char **);
} my_builtins;

int check(char *s, char sign);
int comma(char *user_input);
int divd(char *user_input);
int ali(char **argv);
int exv(char **argv);
int execute(char **argv);
char *_getpath(void);
int cd(char **argv);
int env(char **argv);
int _exi(char **argv);
int comp(char **argv, char *sig);
int _aliass(char *user_input);
int join(char *user_input);
int phars(char *user_input);
int cont(char *userinput, char s);
int seprators(char *user_input);
char *_strcpy(char *dest, char *src);
int coment(char *userinput);
int _check(char *s, char sign);

#endif /* MAIN_H */
