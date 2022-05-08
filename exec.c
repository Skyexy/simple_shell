#include "main.h"

int main(void)
{
    char **argv = malloc(sizeof(char *) * 30);
    argv[0] = "/bin/ls";
    argv[1] = NULL;

    printf("Before execve\n");
    if (execve(argv[0], argv, NULL) == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
