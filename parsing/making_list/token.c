/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:20 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/30 16:22:56 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_second_quotes(char *line, char c, int *i, int *len)
{
	(*i)++;
	(*len)++;
	while (line[*i])
	{
		if (line[*i] == c && (line[*i + 1] != '\0' || line[*i + 1] != ' '
				|| line[*i + 1] != '\t' || line[*i + 1] != '<'
				|| line[*i + 1] != '>' || line[*i + 1] != '|'
				|| line[*i + 1] != '\"' || line[*i + 1] != '\''))
		{
			(*i)++;
			(*len)++;
			break ;
		}
		(*i)++;
		(*len)++;
	}
}

int	count_line(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		if (line[i] == '\'')
			search_second_quotes(line, '\'', &i, &len);
		else if (line[i] == '\"')
			search_second_quotes(line, '\"', &i, &len);
		else if (line[i] != '<' && line[i] != '>' && line[i] != '|')
		{
			i++;
			len++;
		}
		else
			break ;
	}
	return (len);
}

void	chose_type(t_token **new)
{
	if (ft_strcmp((*new)->line, "|") == 0)
		(*new)->type = PIPE;
	else if (ft_strcmp((*new)->line, "<<") == 0)
		(*new)->type = HEREDOC;
	else if (ft_strcmp((*new)->line, ">>") == 0)
		(*new)->type = APPEND;
	else if (ft_strcmp((*new)->line, "<") == 0)
		(*new)->type = INPUT;
	else if (ft_strcmp((*new)->line, ">") == 0)
		(*new)->type = OUTPUT;
	else
		(*new)->type = WORD;
}

void	add_token(t_data_shell *mshell, t_cmd *file, int *i, int len)
{
	t_token	*new;
	t_token	*tmp;

	new = gc_malloc(sizeof(t_token), &file->head);
	if (!new)
		return ;
	else
	{
		new->line = ft_substr(mshell, file->rl, *i, len);
		*i += len;
		chose_type(&new);
		new->next = NULL;
		if (file->token_list == NULL)
			file->token_list = new;
		else
		{
			tmp = file->token_list;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = new;
		}
	}
}

void	token_line(t_data_shell *mshell, t_cmd *file)
{
	int	i;

	i = 0;
	file->token_list = NULL;
	while (file->rl[i])
	{
		if (ft_strncmp(&(file->rl[i]), "|", 1) == 0)
			add_token(mshell, file, &i, 1);
		else if (ft_strncmp(&(file->rl[i]), "<<", 2) == 0)
			add_token(mshell, file, &i, 2);
		else if (ft_strncmp(&(file->rl[i]), ">>", 2) == 0)
			add_token(mshell, file, &i, 2);
		else if (ft_strncmp(&(file->rl[i]), "<", 1) == 0)
			add_token(mshell, file, &i, 1);
		else if (ft_strncmp(&(file->rl[i]), ">", 1) == 0)
			add_token(mshell, file, &i, 1);
		else if (file->rl[i] != ' ' && file->rl[i] != '\t')
			add_token(mshell, file, &i, count_line(file->rl, i));
		else
			i++;
	}
}
