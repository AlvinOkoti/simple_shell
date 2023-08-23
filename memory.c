#include "shell.h"

/**
 * bfree - fre3s up a pointer th3n NULLs the address
 * @ptr: address p0inter t0 free
 *
 * Return: 1 if !s freed, oth3rwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

