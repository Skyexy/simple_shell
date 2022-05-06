#include <stdio.h>
#include <unistd.h>

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
        int int_mode;

        while (int_mode)
        {
                int_mode = isatty(STDIN_FILENO);
                if (int_mode == 1)
                {
                        write(STDOUT_FILENO, "#cisfun$" , 13);
                }
        }
        return (0);
}
