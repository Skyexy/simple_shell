#include "main.h"

/**
 * _strdunp - changes /n to /0
 * Return: lo
 * @lo: the lead string
 */
char *_strdunp(char *lo)
{
	int i;

	for(i=0; i<_strlen(lo); i++)
	{
		if(lo[i]=='\n')
		{      
			lo[i]='\0';
		}
	}
	return (lo);
}

int main(void)
{
        int int_mode;
        size_t buff = 0;
        char **argv = malloc(sizeof(char *) * 512);
        char *input = malloc(sizeof(char) * 512);
        char *token = NULL;
        int counter;
        pid_t son;
        char *current = malloc(sizeof(char) * 512);

        while (int_mode != EOF)
        {
                int_mode = isatty(STDIN_FILENO);
                if (int_mode == 1)
                {
                        write(STDOUT_FILENO, getcwd(current, 120), 120);
                }
                getline(&input,&buff,stdin);
                if (*input == '\n')
                {
                        continue;
                }
                token = strtok(input, " ");
                counter = 0;
                while (token != NULL)
                {
                        argv[counter] = _strdunp(token);
                        token = strtok(NULL, " ");
                        counter++;
                }
                argv[counter] = NULL;
                son = fork();
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
