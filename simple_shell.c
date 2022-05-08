#include "main.h"

int main(void)
{
        int int_mode;
        size_t buff = 1024;
        int counter = 0;
        char *toks[] = {"NULL"};
        char *input = malloc(sizeof(char) * buff);
        char *token = malloc(sizeof(char) * buff);
        
        while (int_mode != EOF)
        {
                int_mode = isatty(STDIN_FILENO);
                if (int_mode == 1)
                {
                        write(STDOUT_FILENO, "#cisfun$ " , 9);
                }
                getline(&input, &buff, stdin);
                token = strtok(input, " ");
                while (token != NULL)
                {
                        toks[counter] = strdup(token);
                        token = strtok(NULL, " ");
                        counter++;
                }
                toks[counter] = token;
                if (execve(toks[0], toks, NULL) == -1)
                 {
                        perror("Error:");
                }
        }
        return (0);
}
