#include "main.h"

int main(void)
{
        int int_mode;
        size_t buff = 0;
        char **argv = malloc(sizeof(char *) * 512);
        char *input = malloc(sizeof(char) * 512);
        char *token = NULL;
        int i;
        char *current = malloc(sizeof(char) * 512);

        while (int_mode != EOF)
        {
                write(1, getcwd(current, 1204), 120);
                getline(&input,&buff,stdin);
                if (*input == '\n')
                {
                        continue;
                }
                token = strtok(input, " ");
                int counter = 0;
                while (token != NULL)
                {
                        argv[counter] = _strdunp(token);
                        token = strtok(NULL, " ");
                        counter++;
                }
                argv[counter] = NULL;
                int son = fork();
                if (son == -1)
                {
                        perror("Error:");
                        return (1);
                }
                if(!son)
                {
                        if (execve(argv[0], argv, NULL) == -1)
                        {
                                getcwd(current, 1204);
                                perror(current);
                        }
                }
                else
                {
                        wait(NULL);
                }
        }
        free(input);
        free(token);
        free(argv);
        free(current);
        return (0);
}
