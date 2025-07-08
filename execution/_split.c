/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _split.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:54:44 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/01 22:54:45 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == c) && (str[i] != c))
			count++;
		i++;
	}
	return (count);
}

static	int	wordlen(const char *str, char c)
{
	int	start;

	start = 0;
	while (str[start] != c && str[start] != '\0')
		start++;
	return (start);
}

static char	*ft_stdup(t_data_shell *p, const char *src, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	str = (char *)gc_malloc((len + 1) * sizeof(char), &p->line.head);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	void	free_split(char **arr, int arrlen)
{
	while (arrlen >= 0)
	{
		free(arr[arrlen]);
		arrlen--;
	}
	free(arr);
}

char	**s_split(t_data_shell *p, char const *s, char c)
{
	char	**str;

	int (i), (j);
	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = gc_malloc(((count_word(s, c) + 1) * sizeof(char *)), &p->line.head);
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			str[j++] = ft_stdup(p, (s + i), wordlen((s + i), c));
			if (!str[j - 1])
			{
				return (free_split(str, j - 1), NULL);
			}
			i += wordlen((s + i), c);
		}
	}
	return (str[j] = NULL, str);
}
