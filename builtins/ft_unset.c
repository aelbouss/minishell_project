/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:44:14 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/01 22:21:41 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


int	ft_unset(t_data_shell *p, t_env **lst, t_cline *node)
{
	int		i;
	t_env	*holder;
	t_env	*tmp;

	if (!p || !lst || !*lst || ! node)
		return (1);
	i = 1;
	while (node->options[i])
	{
		tmp = (*lst);
		holder = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, node->options[i]) == 0)
			{
				if (!holder)
					(*lst) = tmp->next;
				else
					holder->next = tmp->next;
				clear_node(tmp);
				break;
			}
			holder = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
