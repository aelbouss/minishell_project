/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:47:26 by codespace         #+#    #+#             */
/*   Updated: 2025/06/18 14:48:05 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_string_133(t_data_shell *mshell, int c, char const *s)
{
	char	*str;
	int		i;

	i = 0;
	str = gc_malloc((c + 1), &(mshell->line.head));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*join_q(t_data_shell *mshell, char const *s1, char s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == 0)
		return (NULL);
	else if (s2 == 0)
		return (ft_string_133(mshell, ft_strlen(s1), s1));
	else if (s1 == NULL)
	{
		str = gc_malloc(2, &(mshell->line.head));
		str[0] = s2;
		str[1] = '\0';
		return (str);
	}
	str = gc_malloc((ft_strlen(s1) + 2), &(mshell->line.head));
	if (str == NULL)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = s2;
	str[j] = '\0';
	return (str);
}
