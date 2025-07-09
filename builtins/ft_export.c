/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:42:13 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/09 02:44:24 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_node(char *name, char *value)
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
	if (value == NULL)
		node->flag = 1;
	else if (value && value[0] == '\0')
		node->flag = 1;
	else
		node->flag = 0;
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
	char	**arr;
	t_env	*new;

	(void)idx;
	arr = extract_identifier_and_value(p, node->options[1]);
	if(!arr)
		return (1);
	if (check_if_exists(p->env_list, arr[0]) == 1)
	{
		modify_env_var(p->env_list, arr[0], arr[1]);
		clear_2d_arr(arr);
		return (p->exit_status = 0, 0);
	}
	new = create_node(s_strdup(arr[0]), s_strdup(arr[1]));
	if (!new)
		return (perror("Bad Allocation\n"), 1);
	clear_2d_arr(arr);
	add_to_linkedlist(&p->env_list, new);
	return (p->exit_status = 0, 0);
}

int	ft_export(t_data_shell *p, t_cline *node)
{
	int	i;

	if (!p || !p->env_list)
		return (1);
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
