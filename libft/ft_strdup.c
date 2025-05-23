/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:10:01 by codespace         #+#    #+#             */
/*   Updated: 2025/05/02 16:16:05 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*c;

	j = 0;
	i = ft_strlen(s);
	c = malloc(i + 1);
	if (c == NULL)
		return (NULL);
	while (s[j])
	{
		c[j] = s[j];
		j++;
	}
	c[j] = '\0';
	return (c);
}
