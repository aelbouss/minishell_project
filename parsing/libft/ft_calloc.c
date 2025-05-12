/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:39:36 by codespace         #+#    #+#             */
/*   Updated: 2024/11/08 02:23:48 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*c;
	size_t	i;
	size_t	len;

	i = 0;
	len = nmemb * size;
	if (nmemb != 0 && len / nmemb != size)
		return (NULL);
	c = malloc(len);
	if (c == NULL)
		return (NULL);
	while (i < len)
	{
		c[i] = 0;
		i++;
	}
	return (c);
}
