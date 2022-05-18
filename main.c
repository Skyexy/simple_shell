#include "main.h"

int main(void)
{
	char *user_input = malloc(sizeof(char) * BUFFER_LEN);
	size_t buff;
	size_t length;
	char c;

	while (c != EOF)
	{
		write(STDOUT_FILENO, "($) ", 4);
		c = getline(&user_input, &buff, stdin);
		if (c == EOF)
		{
			break;
		}
		length = strlen(user_input);
		if (length == 0)
		{
			break;
		}
		if (user_input[length - 1] == '\n')
		{
			user_input[length - 1] = '\0';
		}
		if (seprators(user_input) == 1)
		{
			continue;
		}
		divd(user_input);
	}
	return (0);
}
