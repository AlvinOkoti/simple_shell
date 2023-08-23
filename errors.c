#include "shell.h"

/**
 * _eputs - Prints an input string Char
 * @str: the string to be Output
 *
 * Return: 0
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes Character c be stderr
 * @c: The character to output
 *
 * Return: Upon success 1.
 * Upon error, -1 is returned, and errno is Appropriately set.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the Character c to given fd
 * @c: The character to Display
 * @fd: The filedescription to write to
 *
 * Return: On succeSs 1.
 * On error, -1 is returned, and errno is Set correctly
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Displays the Input string
 * @str: the string to be Displayed
 * @fd: the filedescriptor to writen to
 *
 * Return: the number of chars input
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

