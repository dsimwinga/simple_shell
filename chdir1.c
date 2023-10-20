#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, preceded
 * with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Unsets an alias.
 * @info: Parameter struct.
 * @str: The alias string to unset.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *f, c;
    int ret;

    f = _strchr(str, '=');
    if (!f)
	return (1);
    c = *f;
    *f = 0;
    ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *f = c;
    return (ret);
}

/**
 * set_alias - Sets an alias.
 * @info: Parameter struct.
 * @str: The alias string to set.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *f;

    f = _strchr(str, '=');
    if (!f)
	return (1);
    if (!*++f)
	return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *f = NULL, *a = NULL;

    if (node)
    {
	f = _strchr(node->str, '=');
	for (a = node->str; a <= f; a++)
	_putchar(*a);
	_putchar('\'');
	_puts(f + 1);
	_puts("'\n");
	return (0);
    }
    return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *f = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
	node = info->alias;
	while (node)
	{
		print_alias(node);
		node = node->next;
	}
	return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
	f = _strchr(info->argv[i], '=');
	if (f)
		set_alias(info, info->argv[i]);
	else
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

