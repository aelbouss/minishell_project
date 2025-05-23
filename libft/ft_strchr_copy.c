/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:42:36 by codespace         #+#    #+#             */
/*   Updated: 2025/04/29 19:18:22 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


//takes  a char and  str  and  check  if  it exists it returns 0 other ways 1
int	ft_strchr_copy(char *s, char c, int *i)
{
	while (s[*i] != '\0')
	{
		if (s[*i] == c)
			return (0);
		(*i)++;
	}
	return (1);
}
