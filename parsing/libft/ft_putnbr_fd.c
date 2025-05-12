/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:32:10 by codespace         #+#    #+#             */
/*   Updated: 2024/11/11 19:31:38 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (fd >= 0)
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', fd);
			nbr = nbr * -1;
		}
		if (nbr > 9)
		{
			ft_putnbr_fd((nbr / 10), fd);
		}
		ft_putchar_fd(((nbr % 10) + '0'), fd);
	}
}
