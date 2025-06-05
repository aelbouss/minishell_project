/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:26:37 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/28 21:35:51 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countsep_expand(char *s)
{
	int	num;

	num = 0;
	while (*s)
	{
		while ((*s == ' ' || (*s >= 9 && *s <= 13)) && *s != '\0')
			s++;
		if (*s != ' ' && (*s < 9 || *s > 13) && *s != '\0')
			num++;
		while (*s != ' ' && (*s < 9 || *s > 13) && *s != '\0')
			s++;
	}
	return (num);
}

char	**ft_free_all_expand(char **strs, int j)
{
	int	i;

	i = j - 1;
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
	return (NULL);
}

char	**ft_makingstring_ex(t_data_shell *mshell, char *s, char **strs)
{
	char	*tmp;

	int (j), (i), (n);
	j = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && (s[i] < 9 || s[i] > 13)) && (i == 0
				|| s[i - 1] == ' ' || (s[i - 1] >= 9 && s[i - 1] <= 13)))
		{
			n = 0;
			tmp = &s[i];
			while (tmp[n] != ' ' && (tmp[n] < 9 || tmp[n] > 13)
				&& tmp[n] != '\0')
				n++;
			strs[j] = ft_substr(mshell, s, i, n);
			if (strs[j] == NULL)
				return (ft_free_all_expand(strs, j));
			j++;
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_spaces(t_data_shell *mshell, char *s)
{
	char	**strs;
	int		nsep;

	if (s == NULL)
		return (NULL);
	nsep = countsep_expand(s);
	strs = gc_malloc(((nsep + 1) * sizeof(char *)), &(mshell->line.head));
	if (!strs)
		return (NULL);
	strs = ft_makingstring_ex(mshell, s, strs);
	return (strs);
}
