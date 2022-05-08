#include "main.h"

size_t _getline(char *buff, size_t n, int stream)
{
	int t;
	
	if ((t = read(stream, buff, n)) == 1)
	{
		return (-1);
	}
        return (n);
}
