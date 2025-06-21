/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:15:31 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/21 17:36:19 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quotes(t_cmd *line)
{
	int	i;

	i = 0;
	while (line->rl[i])
	{
		if (line->rl[i] == '\'')
		{
			i++;
			if (ft_strchr_copy((line->rl), '\'', &i) == 1)
				return (1);
			else
				i++;
		}
		else if (line->rl[i] == '\"')
		{
			i++;
			if (ft_strchr_copy((line->rl), '\"', &i) == 1)
				return (1);
			else
				i++;
		}
		else
			i++;
	}
	return (0);
}

int	check_validate_syntax(t_cmd *file)
{
	t_token	*tmp;

	tmp = file->token_list;
	if (tmp && tmp->type == 0)
		return (1);
	while (tmp && tmp->next)
	{
		if ((tmp->type != 0 && tmp->type != 5) && tmp->next->type != 5)
			return (1);
		else if (tmp->type == 0 && tmp->next->type == 0)
			return (1);
		tmp = tmp->next;
	}
	if (tmp && tmp->type != 5)
		return (1);
	else
		return (0);
}

void	add_nodes_list(t_data_shell *mshell, char **strs)
{
	t_env	*new;
	t_env	*tmp;

	new = gc_malloc(sizeof(t_env), &(mshell->line.head));
	if (new == NULL)
		return ;
	new->name = strs[0];
	new->value = strs[1];
	new->next = NULL;
	if (mshell->env_list == NULL)
		mshell->env_list = new;
	else
	{
		tmp = mshell->env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	env_list(t_data_shell *mshell, char **env)
{
	char	**strs;
	int		i;

	i = 0;
	mshell->env_list = NULL;
	while (env[i])
	{
		strs = NULL;
		strs = ft_split(mshell, env[i], '=');
		add_nodes_list(mshell, strs);
		i++;
	}
	i = 0;
}

int	check_syntax(t_data_shell *mshell, t_cmd *line, t_cline **list)
{
	if (line->rl)
	{
		if (check_quotes(line) == 1)
			return(error_function(mshell));
		else
		{
			line->token_list = NULL;
			token_line(mshell, line);
			if (check_validate_syntax(line) == 1)
				return (error_function(mshell));
			else
			{
				making_list(line, list);
				expand(mshell);
				red_expand(mshell);
				delete_quotes(mshell);
			}
		}
	}
	return (0);
}

