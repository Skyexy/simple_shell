#include "main.h"

int main(void)
{
        int int_mode;
        size_t buff = 1024;
        size_t get;
        int counter = 0;
        int status;
        char **toks = malloc(sizeof(char *) * 1024);
        char *input = malloc(sizeof(char) * buff);
        char *token = malloc(sizeof(char) * buff);
        size_t t;
        
        while (int_mode != EOF)
        {
                int_mode = isatty(STDIN_FILENO);
                if (int_mode == 1)
                {
                        write(STDOUT_FILENO, "#cisfun$" , 13);
                }
                get = getline(&input, &buff, stdin);
                token = strtok(input, " ");
                while (token != NULL)
                {
                        toks[counter] = strdup(token);
                        token = strtok(NULL, " ");
                        counter++;
                }
                toks[counter] = token;
                t = execve(toks[0], toks, NULL);
        }
        return (0);
}
