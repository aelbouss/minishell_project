/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:47:26 by codespace         #+#    #+#             */
/*   Updated: 2025/05/24 10:33:48 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_string(t_data_shell *mshell, int c, char const *s)
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

char	*ft_strjoin(t_data_shell *mshell, char const *s1, char const *s2)
{
	char	*str;
	int		totlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_string(mshell, ft_strlen(s2), s2));
	else if (s2 == NULL)
		return (ft_string(mshell, ft_strlen(s1), s1));
	else
		totlen = ft_strlen(s1) + ft_strlen(s2);
	str = gc_malloc((totlen + 1), &(mshell->line.head));
	if (str == NULL)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
