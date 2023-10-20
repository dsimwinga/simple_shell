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
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
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
                (*buf)[r - 1] = '\0'; /* Remove trailing newline */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t a, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len)    /* We have commands left in the chain buffer */
    {
        j = a; /* Initialize new iterator to current buf position */
        p = buf + a; /* Get pointer for return */

        check_chain(info, buf, &j, a, len);
        while (j < len) /* Iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        a = j + 1; /* Increment past nulled ';'' */
        if (a >= len) /* Reached end of buffer? */
        {
            a = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back pointer to current command position */
        return (_strlen(p)); /* Return length of current command */
    }

    *buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
    return (r); /* Return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @a: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
    ssize_t r = 0;

    if (*a)
        return (0);
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *a = r;
    return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t a, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *u;

    p = *ptr;
    if (p && length)
        s = *length;
    if (a == len)
        a = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    u = _strchr(buf + a, '\n');
    k = u ? 1 + (unsigned int)(u - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + a, k - a);
    else
        _strncpy(new_p, buf + a, k - a + 1);

    s += k - a;
    a = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

