#include "../minishell.h"


int	clear_node(t_env *node)
{

	if (!node)
		return (1);
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
	return (0);
}

int ft_del_start(t_env **lst, t_data_shell *p, int *ptr, t_cline *node)
{
	t_env	*holder;

	if (!lst || !p || !ptr)
		return (1);
	if (!p->list->options[*ptr])
		return (1);
	if (ft_strcmp((*lst)->name, node->options[*ptr]) == 0)
	{
		holder = (*lst);
		(*lst) = (*lst)->next;
		if (clear_node(holder) == 1)
			return(perror("unset() failed\n"), 1);
		*ptr = *ptr + 1;
	}
	return (0);
}

int	ft_unset(t_data_shell *p, t_env **lst, t_cline *node)
{
	int	i;
	t_env	*holder;
	t_env	*tmp;

	if (!p || !lst || !*lst  || ! node)
		return (1);
	i = 1;
	ft_del_start(&p->env_list, p, &i, node);
	while (node->options[i])
	{
		tmp = (*lst);
		while (tmp)
		{
			if (ft_strcmp(tmp->next->name, node->options[i]) == 0)
			{
				holder = tmp->next;
				tmp->next = tmp->next->next;
				if (clear_node(holder) == 1)
					return(perror("unset() failed\n"), 1);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}