#include "../minishell.h"

t_fg	*fg_new(void *ptr)
{
	t_fg	*list;

	list = malloc(sizeof(t_fg));
	if (!list)
		return (NULL);
	else
	{
		list->add = ptr;
		list->next = NULL;
	}
	return (list);
}

void	fg_add_to_list(t_fg **list, t_fg *node)
{
	t_fg	*tmp;

	if (!list || !(*list))
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	*fg_malloc(size_t allocate, t_fg **list)
{
	void	*tmp;

	tmp = malloc(allocate);
	if (!tmp)
		return (NULL);
	fg_add_to_list(list, fg_new(tmp));
	return (tmp);
}

void	fg_free_gc(t_fg **list)
{
	t_fg	*tmp;

	tmp = *list;
	while ((*list))
	{
		*list = (*list)->next;
		if (tmp->add)
			free(tmp->add);
		if (tmp)
			free(tmp);
		tmp = (*list);
	}
	list = NULL;
}
