/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:52 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/12 02:54:27 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_no(t_data_shell *mshell, char *str, int *j)
{
	int		len;
	char	*new;
	char	c;

	len = 0;
	if (str[*j] == '\'' || str[*j] == '"')
	{
		c = str[*j];
		(*j)++;
		while (str[*j + len] && (str[*j + len] != c))
			len++;
		len++;
		new = ft_substr(mshell, str, *j, len - 1);
	}
	else
	{
		while (str[*j + len] && str[*j + len] != '\'' && str[*j + len] != '"')
			len++;
		new = ft_substr(mshell, str, *j, len);
	}
	(*j) += len;
	return (new);
}

char	*new_options(t_data_shell *mshell, t_redr *node, char *tmp)
{
	char	*new_options;
	int		j;

	j = 0;
	if (node && node->type == 1)
		node->h_expand = 1;
	new_options = NULL;
	while (tmp[j] != 0)
		new_options = ft_strjoin(mshell, new_options, ft_no(mshell, tmp, &j));
	return (new_options);
}

void	antimask_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

void	apply_changes(t_data_shell *mshell)
{
	t_cline	*tmp;
	t_redr	*tmp2;
	int		i;

	tmp = mshell->list;
	while (tmp)
	{
		i = 0;
		tmp2 = tmp->r_list;
		while (tmp->options[i])
		{
			antimask_expand(tmp->options[i]);
			i++;
		}
		while (tmp2)
		{
			antimask_expand(tmp2->file);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	delete_quotes(t_data_shell *mshell)
{
	t_cline	*tmp;
	t_redr	*tmp2;
	int		i;

	tmp = mshell->list;
	while (tmp)
	{
		i = 0;
		tmp2 = tmp->r_list;
		while (tmp->options[i])
		{
			if (ft_strchr(tmp->options[i], '\"') != NULL
				|| ft_strchr(tmp->options[i], '\'') != NULL)
				tmp->options[i] = new_options(mshell, NULL, tmp->options[i]);
			i++;
		}
		while (tmp2)
		{
			if ((ft_strchr(tmp2->file, '\"') != NULL || ft_strchr(tmp2->file,
						'\'') != NULL))
				tmp2->file = new_options(mshell, tmp2, tmp2->file);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
