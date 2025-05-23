#include "../minishell.h"

int	print_envs(t_env *lst)
{
	while (lst)
	{
		if (lst->name)
		{
			printf("declare -x ");
			printf("%s",lst->name);
		}
		if (lst->value)
		{
			printf("=");
			printf("%s",lst->value);
		}
		printf("\n");
		lst = lst -> next;
	}
	return (0);
}

void	ft_select_flag(char *s, int *p)
{
	int	i;

	if (search_for_char(s, '=') != 1)
	{
		*p = 2;
		return ;
	}
	i = 0;
	while (s[i])
	{
		if (s[i + 1] == '\0' && s[i] == '=')
		{
			*p = 1;
			return ;
		}
		i++;
	}
}

t_env	*create_node(t_minishell *p, char *name, char *value, int flag)
{
	t_env	*node;

	node = gc_malloc(sizeof(t_env), &p->line.head);
	if (!node)
		return (NULL);
	node->name = name;
	if (!node->name)
		return (perror("export(): invalid identifier"), NULL);
	node->value = value;
	node->next = NULL;
	node->flag = flag;
	if (!value)
	{
		if (flag == 1)
		{
			node->value = ft_strdup("");
			if (!node->value)
				return (perror("Bad Allocation"), NULL);
		}
		if (flag == 2)
			node->value = NULL;
	}
	return (node);
}

int	search_for_char(char *s, int n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == n)
			return (1);
		i++;
	}
	return (0);
}

int	check_to_modify(t_minishell *p, char *name, char *new_value)
{
	t_env *ptol;

	ptol = p->env_head;
	while(ptol)
	{
		if (ft_strcmp(name, ptol->name) == 0)
		{
			if (ptol->value)
			{
				free(ptol->value);
				ptol->value = new_value;
				return (0);
			}
		}
		ptol = ptol->next;
	}
	return (1);
}

int ft_export(t_minishell *p)
{
	char	**arr;
	t_env	*new;
	int		flag;

	if (!p || !p->env_head)
		return (perror("export failed\n") , 1);
	if (!p->list->options[1])
	{
		if (print_envs(p->env_head) == 1)
			return (1);
	}
	else
	{
		flag = 0;
		arr = ft_split(p->list->options[1], '=');
		if (!arr)
			return (perror("Bad Allocation\n"), 1);
		if (check_to_modify(p, arr[0], arr[1]) == 0)
			return (0);
		ft_select_flag(p->list->options[1], &flag);
		new = create_node(p, arr[0], arr[1], flag);
		if (!new)
			return (perror("Bad Allocation\n"), 1);
		add_to_linkedlist(&p->env_head, new);
	}
	return (0);
}

