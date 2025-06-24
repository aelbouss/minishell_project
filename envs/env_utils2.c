#include "../minishell.h"

void	add_to_linkedlist(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !*lst)
		*lst = new ;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	create_env_list(t_data_shell *p, char **envp)
{
	t_env	*newnode;
	int		i;

	p->env_list = NULL ;
	i = 0;
	while (envp[i])
	{
		newnode = build_node(p, envp[i]);
		if (!newnode)
		{
			printf("Bad Allocation\n");
			return ;
		}
		add_to_linkedlist(&p->env_list, newnode);
		i++;
	}
}

char	*concat_and_free(t_data_shell *p, char *s1, char *s2)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(p, s1, "=");
	if (!str1)
		return (perror("Bad Allocation\n"), NULL);
	str2 = ft_strjoin(p, str1, s2);
		if (!str2)
		return (perror("Bad Allocation\n"), NULL);
	return(str2);
}

char	**turn_list_to_arr(t_env *lst, t_data_shell *p)
{
	int		i;
	char	**arr;

	if (!lst || !p)
		return (perror("Bad Allocation\n") ,NULL);
	i = 0;
	i = list_cnt(lst);
   	arr = gc_malloc((sizeof(char *) * (i+1)), &p->line.head);
	if (!arr)
		return (perror("Bad Allocation\n"), NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = concat_and_free(p, lst->name, lst->value); 
		if (!arr[i-1])
			return (perror("Bad Allocation"), NULL);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	list_len(t_cline *lst)
{
	int	i;

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
