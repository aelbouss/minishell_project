/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:19:44 by codespace         #+#    #+#             */
/*   Updated: 2024/11/11 01:32:50 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	size_t	tmp;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (!len)
		return (NULL);
	while (big[i] && len > i)
	{
		tmp = i;
		while (big[tmp] == little[j] && len > tmp)
		{
			tmp++;
			j++;
			if (little[j] == '\0')
				return ((char *)&big[tmp - j]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
