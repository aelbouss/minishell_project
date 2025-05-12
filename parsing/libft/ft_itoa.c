/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:23:09 by memahamo          #+#    #+#             */
/*   Updated: 2024/11/08 02:24:05 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(long n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_is_negatif(long n)
{
	long	nb;
	char	*str;
	int		i;

	n = n * -1;
	nb = n;
	i = ft_count(nb);
	i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	str[0] = '-';
	while (i > 1)
	{
		str[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_is_positif(int n)
{
	int		nb;
	char	*str;
	int		i;

	nb = n;
	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	nb;

	nb = n;
	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
		return (ft_is_negatif(nb));
	else
		return (ft_is_positif(n));
}
