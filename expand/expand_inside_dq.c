/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_inside_dq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:22:43 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:13:55 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ability_to_expand(t_data_shell *mshell, char *str)
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

char	*expand_inside_dq(t_data_shell *mshell, char *str, int *j, int i)
{
	char	*new;

	(*j)++;
	if (str[*j] && str[*j] == '?')
		new = ft_itoa(mshell, mshell->exit_status, j);
	else
	{
		while (str[*j + i] && str[*j + i] != '"'
			&& ft_isalnum(str[*j + i]) != 0)
			i++;
		new = ability_to_expand(mshell, ft_substr(mshell, str, *j, i));
		(*j) += i;
	}
	return (new);
}

char	*change_content_inside_dquotes(t_data_shell *mshell, char *str, int *j,
		int len)
{
	int		i;
	char	*new;
	char	*new_option;

	new_option = NULL;
	while (str[*j] && str[*j] != '"' && *j < len)
	{
		i = 0;
		new = NULL;
		if (str[*j] != '$')
		{
			while (str[*j + i] && str[*j + i] != '"' && str[*j + i] != '$')
				i++;
			new = ft_substr(mshell, str, *j, i);
		}
		else
			new = expand_inside_dq(mshell, str, j, i);
		if (str[*j + i] && str[*j + i] == '"')
			(*j)++;
		(*j) += i;
		new_option = ft_strjoin(mshell, new_option, new);
	}
	return (new_option);
}

char	*dq_fct(t_data_shell *mshell, char *str, int *j)
{
	int		len;
	char	*mdf_option;

	len = 0;
	mdf_option = NULL;
	if (ft_strchr(&(str[*j]), '$') != NULL)
	{
		(*j)++;
		while (str[*j + len] && str[*j + len] != '"')
			len++;
		if (len == 0)
		{
			(*j)++;
			return (NULL);
		}
		len += *j;
		mdf_option = ft_strjoin(mshell, mdf_option, "\"");
		mdf_option = ft_strjoin(mshell, mdf_option,
				change_content_inside_dquotes(mshell, str, j, len));
		mdf_option = ft_strjoin(mshell, mdf_option, "\"");
		return (mdf_option);
	}
	else
		return (no_expand(mshell, str, j));
}
