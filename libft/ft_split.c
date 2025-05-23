/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:24:53 by codespace         #+#    #+#             */
/*   Updated: 2025/04/29 19:38:00 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int 	len(const char *s, int i)
{
	int len;
	int j;

	len  = 0;
	j = 0;
	if (i == 0)
	{
		while (s[len] && s[len] != '=')
			len++;
		// if ()
		// len++;
		return len;
	}
	else
	{
		while (s[j] && s[j] != '=')
			j++;
		j++;
		while (s[j + len])
			len++;
		return len;
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
	free (strs);
	return (NULL);
}

char	**ft_makingstrings(const char *s, char **strs, char c)
{
	int			j;
	int			i;
	//int			n;
	//const char	*tmp;

	j = 0;
	i = 0;
	//n = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c) && j < 2)
		{
			//tmp = &s[i];
			strs[j] = ft_substr(s, i, len(s, i));
			if (strs[j] == NULL)
				return (ft_free_all(strs, j));
			j++;
			//n = 0;
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = malloc((2 + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = ft_makingstrings(s, strs, c);
	return (strs);
}
