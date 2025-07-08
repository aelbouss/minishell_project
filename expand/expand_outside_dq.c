/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_outside_dq.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:32:14 by mery              #+#    #+#             */
/*   Updated: 2025/05/28 17:46:24 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countsep(char const *s)
{
	int	num;

	num = 0;
	if (s && *s)
	{
		while (*s)
		{
			while ((*s == ' ' || (*s >= 9 && *s <= 13)) && *s != '\0')
				s++;
			if (*s != ' ' && (*s < 9 || *s > 13) && *s != '\0')
				num++;
			while (*s != ' ' && (*s < 9 || *s > 13) && *s != '\0')
				s++;
		}
	}
	return (num);
}

char	*out_quotes(t_data_shell *mshell, t_cline *tmp, int *j, t_exp_info *vr)
{
	char	*result;
	int		i;

	i = 0;
	(*j)++;
	if (tmp->options[tmp->index_2][*j] && tmp->options[tmp->index_2][*j] == '?')
		result = ft_itoa(mshell, mshell->exit_status, j);
	else
	{
		while (tmp->options[tmp->index_2][*j + i]
			&& ft_isalnum(tmp->options[tmp->index_2][*j + i]) != 0)
			i++;
		result = ability_to_expand(mshell, ft_substr(mshell,
					tmp->options[tmp->index_2], *j, i));
		*j += i;
		if (result && countsep(result) >= 1)
		{
			vr->count_word = countsep(result);
			vr->expand_result = ft_split_spaces(mshell, result);
			return (vr->expand_result[0]);
		}
	}
	return (result);
}

void	update_optns(t_data_shell *mshell, t_cline *tmp, t_exp_info *vr,
		int *chnage_i2)
{
	char	**new_options;

	int (i), (j);
	i = 0;
	j = 1;
	new_options = gc_malloc(((vr->count_word + tmp->len_options + 1)
				* sizeof(char *)), &(mshell->line.head));
	tmp->len_options += (vr->count_word - 1);
	while (i < tmp->index_2)
	{
		new_options[i] = tmp->options[i];
		i++;
	}
	new_options[i++] = ft_strdup(mshell, vr->mdf_option);
	while (vr->expand_result[j])
		new_options[i++] = vr->expand_result[j++];
	*chnage_i2 = i - 1;
	while (tmp->options[i - j + 1])
	{
		new_options[i] = tmp->options[i - j + 1];
		i++;
	}
	new_options[i] = 0;
	tmp->options = new_options;
}

void	check_to_split(t_data_shell *mshell, t_cline *tmp, t_exp_info *vr,
		int *j)
{
	char	*reserve;
	int		change_i2;

	change_i2 = 0;
	reserve = NULL;
	reserve = ft_substr(mshell, tmp->options[tmp->index_2], *j,
			ft_strlen(tmp->options[tmp->index_2]) - *j);
	update_optns(mshell, tmp, vr, &change_i2);
	tmp->index_2 = change_i2;
	if (reserve && *reserve)
	{
		*j = ft_strlen(tmp->options[tmp->index_2]);
		tmp->options[tmp->index_2] = ft_strjoin(mshell,
				tmp->options[tmp->index_2], reserve);
	}
}
