#ifndef MAIN_H
#define MAIN_H

typedef struct ali {
     char *name;
     int (*func)(void);
} alias;
alias aliases[] = {
     {"name", function},
     {NULL, NULL}
};
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#endif /* MAIN_H */
