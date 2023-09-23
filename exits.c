#include "shell.h"

/**
 **_strncpy - string copies
 *@dest: destination string to be copied
 *@src: string source
 *@n: number of Chars to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, j;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		j = a;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenation of two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, j;
	char *s = dest;

	a = 0;
	j = 0;
	while (dest[a] != '\0')
		a++;
	while (src[j] != '\0' && j < n)
	{
		dest[a] = src[j];
		a++;
		j++;
	}
	if (j < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - locates a Char in string
 *@s: string to be parsed
 *@c: Char to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

