#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
        int int_mode;
        char **toks = malloc(sizeof(char *) * 1024);
        char *token;
        int counter = 0;

        while (int_mode != EOF)
        {
                int_mode = isatty(STDIN_FILENO);
                if (int_mode == 1)
                {
                        write(STDOUT_FILENO, "#cisfun$" , 13);
                }
                token = strtok(*av, " ");
                while (token != NULL)
                {
                        toks[counter] = strdup(token);
                        token = strtok(NULL, " ");
                        counter++;
                }
                toks[counter] = token;
        }
        return (0);
}
