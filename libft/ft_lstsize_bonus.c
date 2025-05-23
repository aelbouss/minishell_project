/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:20:05 by memahamo          #+#    #+#             */
/*   Updated: 2024/11/08 02:24:42 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		nombre;
	t_list	*tmp;

	nombre = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		nombre++;
		tmp = tmp->next;
	}
	return (nombre);
}
