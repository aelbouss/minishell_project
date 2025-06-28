#include "../minishell.h"

void	faileur(int ex, t_data_shell *p)
{
	fg_free_gc(&p->fgc);
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
		if (lst->d_flag == 0)
			i++;
		lst = lst->next;
	}
	return (i);
}
