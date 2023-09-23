#include "shell.h"

/**
 * _memset - fills the memory with a constant byte
 * @s: memory area pointer
 * @b: fills byte with *
 * @n: number of bytes to fill
 * Return: (s) memory area pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - frees string of string
 * @pp: string of string
 */
void ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(i);
}

/**
 * _realloc - memory block reallocation
 * @ptr: previous mallocated block pointer
 * @old_size: previous block byte size
 * @new_size: new block byte size
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *u;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	u = malloc(new_size);
	if (!u)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		u[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (u);
}
