/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:45:00 by codespace         #+#    #+#             */
/*   Updated: 2024/11/11 01:34:31 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	cc;
	char	*str;

	i = 0;
	cc = (char)c;
	str = (char *)s;
	while (n > i)
	{
		if (str[i] == cc)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
