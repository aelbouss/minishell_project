/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:42:13 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/01 18:34:02 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_env	*create_node(char *name, char *value, int flag)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
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
			node->value = s_strdup("");
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
	t_env	*ptol;

	ptol = p->env_list;
	while (ptol)
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

int	creation_routine(t_data_shell *p, t_cline *node, int idx)
{
	int		flag;
	char	**arr;
	t_env	*new;

	flag = 0;
	arr = fg_split(node->options[idx], '=');
	if (!arr)
		return (perror("Bad Allocation\n"), 1);
	if (check_to_modify(p, arr[0], arr[1]) == 0)
		return (0);
	ft_select_flag(node->options[1], &flag);
	if (is_valid_identifier(arr[0][0]) != 0)
	{
		printf("Minishell : export: %s : not a valid identifier\n", arr[0]);
		p->exit_status = 1;
		return (1);
	}
	new = create_node(arr[0], arr[1], flag);
	if (!new)
		return (perror("Bad Allocation\n"), 1);
	add_to_linkedlist(&p->env_list, new);
	return (0);
}

int	ft_export(t_data_shell *p, t_cline *node)
{
	int	i;

	if (!p || !p->env_list)
		return (perror("export failed\n"), 1);
	if (!node->options[1])
	{
		if (print_envs(p->env_list) == 1)
			return (1);
	}
	else
	{
		i = 1;
		while (node->options[i])
		{
			if (creation_routine(p, node, i) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}
