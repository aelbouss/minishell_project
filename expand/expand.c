/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:41:03 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/27 22:52:58 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*no_expand(t_data_shell *mshell, char *str, int *j)
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
		new = ft_substr(mshell, str, *j - 1, len + 2);
		(*j) += len + 1;
		return (new);
	}
	else
	{
		while (str[*j + len] && str[*j + len] != '\'' && str[*j + len] != '"'
			&& str[*j + len] != '$')
			len++;
		new = ft_substr(mshell, str, *j, len);
		(*j) += len;
		return (new);
	}
}

char	*check_expnd(t_data_shell *mshell, t_cline *tmp)
{
	t_exp_info	vr;
	int			j;

	vr.mdf_option = NULL;
	vr.count_word = 0;
	j = 0;
	while (tmp->options[tmp->index_2][j])
	{
		vr.return_fnct = NULL;
		if (tmp->options[tmp->index_2][j] == '"')
			vr.return_fnct = dq_fct(mshell, tmp->options[tmp->index_2], &j);
		else if (tmp->options[tmp->index_2][j] != '$')
			vr.return_fnct = no_expand(mshell, tmp->options[tmp->index_2], &j);
		else if (tmp->options[tmp->index_2][j] == '$')
			vr.return_fnct = (out_quotes(mshell, tmp, &j, &vr));
		vr.mdf_option = ft_strjoin(mshell, vr.mdf_option, vr.return_fnct);
		if (vr.count_word > 1)
		{
			check_to_split(mshell, tmp, &vr, &j);
			j = ft_strlen(tmp->options[tmp->index_2]);
		}
	}
	return (vr.mdf_option);
}

char	**remove_null(t_data_shell *mshell, t_cline *tmp, int len)
{
	char	**new_options;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_options = gc_malloc((len + 1) * sizeof(char *), &(mshell->line.head));
	if (!new_options)
		return (NULL);
	while (i < tmp->len_options)
	{
		if (tmp->options[i] != NULL)
		{
			new_options[j] = tmp->options[i];
			j++;
		}
		i++;
	}
	new_options[j] = 0;
	return (new_options);
}

void	resize_options(t_data_shell *mshell)
{
	t_cline	*tmp;
	int		new_len;
	int		i;

	tmp = mshell->list;
	while (tmp)
	{
		i = 0;
		new_len = 0;
		while (i < tmp->len_options)
		{
			if (tmp->options[i] != NULL)
				new_len++;
			i++;
		}
		tmp->options = remove_null(mshell, tmp, new_len);
		tmp = tmp->next;
	}
}

void	expand(t_data_shell *mshell)
{
	t_cline	*tmp;
	int		i;
	int		j;

	tmp = mshell->list;
	j = 0;
	while (tmp)
	{
		i = 0;
		tmp->index_1 = j;
		tmp->len_options = 0;
		while (tmp->options[tmp->len_options])
			tmp->len_options++;
		while (i < tmp->len_options)
		{
			tmp->index_2 = i;
			if (tmp->options[i] && ft_strchr(tmp->options[i], '$') != NULL)
				tmp->options[i] = check_expnd(mshell, tmp);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
	resize_options(mshell);
}
