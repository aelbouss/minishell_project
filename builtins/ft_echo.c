/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:32 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/05 16:51:03 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	looking_for_char(char *s, int n)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != n)
			return (1);
		i++;
	}
	return (0);
}

int	ft_search(char *s, char  c)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;

	if (!args || !args[1])
		return (printf("\n"), 0);
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && looking_for_char(args[i], 'n') == 0)
			i++;
		else
			break ;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (i > 0)
			printf(" ");
		i++;
	}
	if (!ft_search(args[1], 'n'))
		printf("\n");
	return (0);
}
