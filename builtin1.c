#include "shell.h"

/**
 * _myhistory - displays history list.
 * @info: contains structure of potential arguments.
 *       .
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: struct parameter
 * @str: alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *u, v;
	int ret;

	u = _strchr(str, '=');
	if (!u)
		return (1);
	v = *u;
	*u = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*u = v;
	return (ret);
}

/**
 * set_alias - sets alias > string
 * @info: struct parameter
 * @str: alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *u;

	u = _strchr(str, '=');
	if (!u)
		return (1);
	if (!*++u)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: node of alias
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *u = NULL, *i = NULL;

	if (node)
	{
		u = _strchr(node->str, '=');
		for (i = node->str; i <= u; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(u + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics builtin alias (man alias)
 * @info: contains structure of potential arguments.
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *u = NULL;
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
	for (a = 1; info->argv[a]; a++)
	{
		u = _strchr(info->argv[a], '=');
		if (u)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}

