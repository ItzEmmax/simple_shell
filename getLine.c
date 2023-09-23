#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, j, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = a; /* init new iterator to current buf position */
		p = buf + a; /* get pointer for return */

		check_chain(info, buf, &j, a, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		a = j + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}


/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: s
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _getline - receives next line of input from STDIN
 * @info: struct parameter
 * @ptr: preallocated or NULL pointer address to buffer
 * @length: preallocated ptr buffer if not NULL size
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t t;
	ssize_t s = 0, x = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		x = *length;
	if (a == len)
		a = len = 0;

	s = read_buf(info, buf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	t = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, x, x ? x + t : t + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (x)
		_strncat(new_p, buf + a, t - a);
	else
		_strncpy(new_p, buf + a, t - a + 1);

	x += t - a;
	a = t;
	p = new_p;

	if (length)
		*length = x;
	*ptr = p;
	return (x);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: number signal
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
