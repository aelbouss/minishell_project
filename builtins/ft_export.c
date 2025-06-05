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

t_env	*create_node(t_data_shell *p, char *name, char *value, int flag)
{
	t_env	*node;

	node = fg_malloc(sizeof(t_env), &p->fgc);
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
			node->value = s_strdup(p, "");
			if (!node->value)
				return (perror("Bad Allocation"), NULL);
		}
		if (flag == 2)
			node->value = NULL;
	}
	return (node);
}

int	check_to_modify(t_data_shell *p, char *name, char *new_value)
{
	t_env *ptol;

	ptol = p->env_list;
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

int ft_export(t_data_shell *p, t_cline *node)
{
	char	**arr;
	t_env	*new;
	int		flag;

	if (!p || !p->env_list)
		return (perror("export failed\n") , 1);
	if (!node->options[1])
	{
		if (print_envs(p->env_list) == 1)
			return (1);
	}
	else
	{
		flag = 0;
		arr = fg_split(p, node->options[1], '=');
		if (!arr)
			return (perror("Bad Allocation\n"), 1);
		if (check_to_modify(p, arr[0], arr[1]) == 0)
			return (0);
		ft_select_flag(node->options[1], &flag);
		new = create_node(p, arr[0], arr[1], flag);
		if (!new)
			return (perror("Bad Allocation\n"), 1);
		add_to_linkedlist(&p->env_list, new);
	}
	return (0);
}
