#include "shell.h"

/**
 **_strncpy - copies TO a string
 *@dest: the destination string to be copied into
 *@src: the source string chaR
 *@n: the amount of CHARs to be copied
 *Return: the concatenated String
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates THE Two strings
 *@dest: the first string CHAR
 *@src: the second string CHAR
 *@n: the amount of bytes to be optimally used
 *Return: the concatenated string CHAR
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates char IN string CHAR
 *@s: the string SET to be parsed CODE
 *@c: the CHARs to Search FOR
 *Return: (s) a Pointer to THE Memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

