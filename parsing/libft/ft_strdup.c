/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:10:01 by codespace         #+#    #+#             */
/*   Updated: 2025/05/28 17:38:01 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(t_data_shell *mshell, const char *s)
{
	char	*c;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(s);
	c = gc_malloc((i + 1), &(mshell->line.head));
	if (c == NULL)
		return (NULL);
	while (s && s[j])
	{
		c[j] = s[j];
		j++;
	}
	c[j] = '\0';
	return (c);
}
