/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:52 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/30 16:23:57 by aelbouss         ###   ########.fr       */
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

char	*new_options(t_data_shell *mshell, char *tmp)
{
	char	*new_options;
	int		j;

	j = 0;
	new_options = NULL;
	while (tmp[j])
	{
		new_options = ft_strjoin(mshell, new_options, ft_no(mshell, tmp, &j));
	}
	return (new_options);
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
				tmp->options[i] = new_options(mshell, tmp->options[i]);
			i++;
		}
		while (tmp2)
		{
			if (ft_strchr(tmp2->file, '\"') != NULL || ft_strchr(tmp2->file,
					'\'') != NULL)
				tmp2->file = new_options(mshell, tmp2->file);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
// tmp = mshell->list;
// while(tmp)
// {
//     printf ("------------------\n");
//     tmp2 = tmp->r_list;
//     i = 0;
//     while(tmp->options[i])
//     {
//         printf("options : %s\n",tmp->options[i]);
//         i++;
//     }
//     while(tmp2)
//     {
//         printf("red : %d file: %s flag: %d\n",
//  tmp2->type, tmp2->file, tmp2->ambiguous);
//         tmp2 = tmp2->next;
//     }
//     tmp = tmp->next;
//     printf ("------------------\n");
// }
