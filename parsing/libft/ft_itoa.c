/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:23:09 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/27 22:24:24 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_is_negatif(t_data_shell *mshell, long n)
{
	char	*str;
	long	nb;
	int		i;

	n = n * -1;
	nb = n;
	i = ft_count(nb);
	i++;
	str = gc_malloc((i + 1), &(mshell->line.head));
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

char	*ft_is_positif(t_data_shell *mshell, int n)
{
	char	*str;
	int		nb;
	int		i;

	nb = n;
	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	str = gc_malloc((i + 1), &(mshell->line.head));
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

char	*ft_itoa(t_data_shell *mshell, int n, int *j)
{
	long	nb;

	nb = n;
	(*j)++;
	if (n == 0)
		return (ft_strdup(mshell, "0"));
	else if (n < 0)
		return (ft_is_negatif(mshell, nb));
	else
		return (ft_is_positif(mshell, n));
}
