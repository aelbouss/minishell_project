/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:24:53 by codespace         #+#    #+#             */
/*   Updated: 2025/05/28 21:36:03 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len(const char *s, int i)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	if (i == 0)
	{
		while (s[len] && s[len] != '=')
			len++;
		return (len);
	}
	else
	{
		while (s[j] && s[j] != '=')
			j++;
		j++;
		while (s[j + len])
			len++;
		return (len);
	}
}

char	**ft_free_all(char **strs, int j)
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

char	**ft_makingstrings(t_data_shell *mshell, const char *s, char **strs,
						char c)
{
	const char	*tmp;
	int			j;
	int			i;
	int			n;

	j = 0;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c) && j < 2)
		{
			tmp = &s[i];
			strs[j] = ft_substr(mshell, s, i, len(s, i));
			if (strs[j] == NULL)
				return (ft_free_all(strs, j));
			j++;
			n = 0;
		}
		i++;
	}
	strs[j] = NULL;
	(void)tmp;
	(void)n;
	return (strs);
}

char	**ft_split(t_data_shell *mshell, char const *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = gc_malloc(((2 + 1) * sizeof(char *)), &(mshell->line.head));
	if (!strs)
		return (NULL);
	strs = ft_makingstrings(mshell, s, strs, c);
	return (strs);
}
