/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_her.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:19:13 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/12 00:33:42 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ability_to_expand_2(t_data_shell *mshell, char *str)
{
	t_env	*tmp;
	char	*new;

	tmp = mshell->env_list;
	new = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			new = gc_malloc(ft_strlen(tmp->value), &(mshell->line.head));
			if (!new)
				return (NULL);
			new = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (new);
}

char	*out_quotes_her(t_data_shell *mshell, char *line, int *j)
{
	char	*result;
	int		i;

	i = 0;
	(*j)++;
	if (line[*j] && line[*j] == '?')
		result = ft_itoa(mshell, mshell->exit_status, j);
	else
	{
		while (line[*j + i] && ft_isalnum(line[*j + i]) != 0)
			i++;
		result = ability_to_expand_2(mshell, ft_substr(mshell, line, *j, i));
		*j += i;
	}
	return (result);
}

char	*no_expand_her(t_data_shell *mshell, char *str, int *j, char c)
{
	int		len;
	char	*new;

	len = 0;
	while (str[*j + len] && str[*j + len] != c && str[*j + len] != '$')
		len++;
	new = ft_substr(mshell, str, *j, len);
	(*j) += len;
	return (new);
}

char	*expand_inside_dq_her(t_data_shell *mshell, char *str, t_exp_info *her)
{
	int		i;
	char	*new;

	i = 0;
	(her->j2)++;
	if (str[her->j2] && str[her->j2] == '?')
		new = ft_itoa(mshell, mshell->exit_status, &(her->j2));
	else
	{
		while (str[her->j2 + i] && str[her->j2 + i] != her->q_char
			&& ft_isalnum(str[her->j2 + i]) != 0)
			i++;
		new = ability_to_expand_2(mshell, ft_substr(mshell, str, her->j2, i));
		(her->j2) += i;
	}
	return (new);
}
