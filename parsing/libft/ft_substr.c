/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:07:52 by codespace         #+#    #+#             */
/*   Updated: 2025/05/24 10:36:12 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(t_data_shell *mshell, char const *s, unsigned int start,
				size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	ls;

	i = 0;
	if (s == NULL)
		return (NULL);
	ls = ft_strlen(s);
	if (start > ls)
		len = 0;
	else if (start + len > ls)
		len = ls - start;
	str = gc_malloc((len + 1), &(mshell->line.head));
	if (str == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
