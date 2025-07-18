/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:32 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/11 23:30:26 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	looking_for_char(char *s, int n)
{
	int	i;

	i = 1;
	if (!s || !s[i])
		return (1);
	while (s[i])
	{
		if (s[i] != n)
			return (1);
		i++;
	}
	return (0);
}

int	ft_search(char *s, char c)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	else
		i++;
	while (s[i])
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, t_data_shell *p)
{
	int	i;

	if (!args || !args[1] || !args[1][0])
		return (printf("\n"), p->exit_status = 0, 0);
	i = 1;
	while (args[i])
	{
		if (args[1][0] == '\0')
			i++;
		if (args[i][0] == '-' && !looking_for_char(args[i], 'n'))
			i++;
		else
			break ;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!ft_search(args[1], 'n'))
		printf("\n");
	p->exit_status = 0;
	return (0);
}
