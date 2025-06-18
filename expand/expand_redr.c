/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 06:20:28 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/18 21:17:20 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	error_function(t_data_shell *mshell)
{
	ft_putstr_fd("ERROR\n Syntaxe invalide\n", 2);
	free_gc(&(mshell->line.head));
	return (1);
}

char	*out_quotes_red(t_data_shell *mshell, char *tmp, int *j)
{
	char	*result;
	int		i;

	(*j)++;
	i = 0;
	if (tmp[*j] && tmp[*j] == '?')
		result = ft_itoa(mshell, mshell->exit_status, j);
	else
	{
		while (tmp[*j + i] && ft_isalnum(tmp[*j + i]) != 0)
			i++;
		result = ability_to_expand(mshell, ft_substr(mshell, tmp, *j, i));
		*j += i;
	}
	return (result);
}

char	*check_expnd_redr(t_data_shell *mshell, char *tmp, int *check)
{
	char	*f_str;
	char	*e_str;
	int		i;

	e_str = NULL;
	i = 0;
	*check = 0;
	while (tmp[i])
	{
		f_str = NULL;
		if (tmp[i] == '"')
			f_str = dq_fct(mshell, tmp, &i);
		else if (tmp[i] != '$')
			f_str = no_expand(mshell, tmp, &i);
		else if (tmp[i] == '$')
		{
			f_str = (out_quotes_red(mshell, tmp, &i));
			*check = countsep(f_str);
		}
		e_str = ft_strjoin(mshell, e_str, f_str);
	}
	return (e_str);
}

void	red_expand(t_data_shell *mshell)
{
	t_cline	*tmp;
	t_redr	*tmp2;
	char	*reserve;
	int		check;

	tmp = mshell->list;
	while (tmp)
	{
		tmp2 = tmp->r_list;
		while (tmp2)
		{
			if (tmp2->type != HEREDOC && ft_strchr(tmp2->file, '$') != NULL)
			{
				reserve = tmp2->file;
				tmp2->file = check_expnd_redr(mshell, tmp2->file, &check);
				if (tmp2->file == NULL || check > 1)
				{
					tmp2->file = reserve;
					tmp2->ambiguous = 1;
				}
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
