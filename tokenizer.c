#include "shell.h"

/**
 * **strtow - splits string into words
 * @str: input string
 * @d: delimeter string
 * Return: array of strings pointer, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, j, t, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[a], d))
			a++;
		t = 0;
		while (!is_delim(str[a + t], d) && str[a + t])
			t++;
		s[j] = malloc((t + 1) * sizeof(char));
		if (!s[j])
		{
			for (t = 0; t < j; t++)
				free(s[t]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < t; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits string into words
 * @str: input string
 * @d: delimeter
 * Return: array of strings pointer, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, j, t, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		t = 0;
		while (str[a + t] != d && str[a + t] && str[a + t] != d)
			t++;
		s[j] = malloc((t + 1) * sizeof(char));
		if (!s[j])
		{
			for (t = 0; t < j; t++)
				free(s[t]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < t; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
