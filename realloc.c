#include "shell.h"

/**
 * _memset - fills memory with th3!r constant byte
 * @s: p0!nt3r t0 m3mory ar3a 
 * @b: the byte to fill w!th
 * @n: the amount of bytez t0 f!ll
 * * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - freez of strings
 * @pp: string of ztringz
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates bl0ck of memory
 * @ptr: pointer mall0c l0k lock
 * @old_size: byte size of bockbloyc wauchk
 * @new_size: byte size of new bockbloy
 *
 * Return: the oldblock bwoy.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

