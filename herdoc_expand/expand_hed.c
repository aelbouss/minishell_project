/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:16:09 by mery              #+#    #+#             */
/*   Updated: 2025/07/01 23:43:21 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_content_her(t_data_shell *mshell, char *str, t_exp_info *her)
{
	char	*new;
	char	*new_option;

	new_option = NULL;
	while (str[her->j2] && str[her->j2] != her->q_char && her->j2 < her->len)
	{
		new = NULL;
		if (str[her->j2] != '$')
			new = no_expand_her(mshell, str, &(her->j2), her->q_char);
		else
			new = expand_inside_dq_her(mshell, str, her);
		if (str[her->j2] && str[her->j2] == her->q_char)
			(her->j2)++;
		new_option = ft_strjoin(mshell, new_option, new);
	}
	return (new_option);
}

char	*dq_fct_her(t_data_shell *mshell, char *str, t_exp_info *her)
{
	char	*rslt;

	rslt = NULL;
	her->len = 0;
	if (ft_strchr(&(str[her->j2]), '$') != NULL)
	{
		(her->j2)++;
		while (str[her->j2 + her->len]
			&& str[her->j2 + her->len] != her->q_char)
			her->len++;
		if (her->len != 0)
			her->len += her->j2;
		rslt = join_q(mshell, rslt, her->q_char);
		rslt = ft_strjoin(mshell, rslt, change_content_her(mshell, str, her));
		rslt = join_q(mshell, rslt, her->q_char);
		return (rslt);
	}
	else
		return (no_expand(mshell, str, &(her->j2)));
}

char	*her_fcts(t_data_shell *mshell, char *line)
{
	char		*new;
	char		*new2;
	t_exp_info	her;

	her.j2 = 0;
	new2 = NULL;
	while (line[her.j2])
	{
		new = NULL;
		if (line[her.j2] == '$')
			new = out_quotes_her(mshell, line, &(her.j2));
		else if (line[her.j2] == '"' || line[her.j2] == '\'')
		{
			her.q_char = line[her.j2];
			new = dq_fct_her(mshell, line, &her);
		}
		else
			new = no_expand(mshell, line, &(her.j2));
		new2 = ft_strjoin(mshell, new2, new);
	}
	free(line);
	return (new2);
}
