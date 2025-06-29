#include "../minishell.h"

void	faileur(int ex, t_data_shell *p)
{
	free_env_stuff(p->env_list);
	p->env_list = NULL;
	free_gc(&p->line.head);
	exit(ex);
}

int		cnt_nodes(t_env *lst)
{
	int		i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	free_env_stuff(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	_clear_2d_arr_(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}



