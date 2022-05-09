#include "main.c"

/**
 * _strlen -  function that returns the length of a string
 * @s: char type pointer
 *
 * Return: string length of a string
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
	}
	return (i);
}

/**
 * _strncat - concentrates two srings
 * Return: dest
 * @dest: the lead string
 * @src: this is the baby string
 * @n: is the number of string to be conc
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;
	int k;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (k = 0; src[k] != '\0'; k++)
	{
	}
	if (n > k)
	{
		for (j = 0; src[j] != '\0'; i++, j++)
		{
			dest[i] = src[j];
		}
	}
	if (n <= k)
	{
		for (j = 0; j < n; i++, j++)
		{
			dest[i] = src[j];
		}
	}
	return (dest);
}

/**
 * _strdunp - changes /n to /0
 * Return: lo
 * @lo: the lead string
 */
char *_strdunp(char *lo)
{
	int i;

	for(i=0; i<strlen(lo); i++)
	{
		if(lo[i]=='\n')
		{      
			lo[i]='\0';
		}
	}
	return (lo);
}
