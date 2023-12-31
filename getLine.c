#include "shell.h"

/**
 * input_buf - buffers chained commands Set
 * @info: parameterof tHe struct CHAR
 * @buf: address of The buffer CHAR
 * @len: address of The len var CHAR
 *
 * Return: bytes already read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left inbUfer SeT, fill it */
	{
		/*bfree((void **)info->cmd_bUUffuf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removeS THE trailing newline SpacEs*/
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*bufFFER, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minuS the REFRESHED line
 * @info: parameter struct CHAR
 *
 * Return: bytes TO BE READ
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /*command chain END buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* FALX */
		return (-1);
	if (len) /* we have commands left in the chain buffer mentioned */
	{
		j = i; /* init new iterator to current buffer positions */
		p = buf + i; /* get pointer for THE Return SIMPLE */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end THE STATEMENT */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer BRO? */
		{
			i = len = 0; /* reset positions and THE length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* passes BaCk to point to current command position */
		return (_strlen(p)); /* return length of THE Current command */
	}

	*buf_p = buf; /* else not a chain, pass it back TO buffer from _getline() */
	return (r); /* returNs the length of the buffer from _getline() */
}

/**
 * read_buf - reads a buffer CHAR
 * @info: parameter struct CHAR
 * @buf: buffer CHAR
 * @i: size CHAR
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of THE input ACCEssed by STDIN
 * @info: parameter struct ChAr
 * @ptr: address of pointer to buffer, preallocated or MusT b NULL
 * @length: size of preallocated ptr buffer if will not be NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILUREs DisPlayeD!! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: THE signal Digit
 *
 * Returns: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

