#include "main.h"

int main(void)
{
        int int_mode;
        size_t buff = 1024;
        size_t get;
        int counter = 0;
        pid_t pid;
        int status;
        char **toks = malloc(sizeof(char *) * 1024);
        char *input = malloc(sizeof(char) * buff);
        char *token = malloc(sizeof(char) * buff);
        
        pid = fork();
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
                if (pid == -1)
                {
                        perror("Error:");
                        return (1);
                }
                if(!pid)
                {
                        if ((execve(toks[0], toks, NULL)) == -1)
                        {
                                perror("Error: ");
                        }
                }
                else
                {
                        wait(&status);
                }
        }
        return (0);
}
