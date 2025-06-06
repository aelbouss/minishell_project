/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:38:21 by codespace         #+#    #+#             */
/*   Updated: 2025/05/22 10:33:20 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	j;

	j = 0;
	if (!dst)
		return (ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	while (src[j] && size > 0 && (size - 1) > j)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}
