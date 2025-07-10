/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:39:06 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 05:55:42 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long double	ft_atold(const char *str)
{
	long double		result;
	int				i;
	int				sign;
	int				check;

	i = 0;
	result = 0;
	sign = 1;
	check = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		check++;
	}
	return (result * sign);
}

int	validate_argument(t_data_shell *p,  char *arg)
{
	int			i;
	long double	nbr;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (!arg[i])
			return (1);
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			printf("Minishell: exit: %s : numeric argument required\n", arg);
			close_fds_a(p);
			exit (2);
		}
		i++;
	}
	nbr = ft_atold(arg);
	if (nbr > LLONG_MAX || nbr < LLONG_MIN)
	{
		printf("Minishell: exit: %.0Lf: numeric argument required\n", nbr);
		return(p->exit_status = 2, 1);
	}
	return (0);
}

int	ft_exit(t_cline *node, t_data_shell *p)
{
	int	exit_status;

	if (node->options[1] && node->options[2])
	{
		if (numeric_string(node->options[1]) == 0 && numeric_string(node->options[2]) == 0)
		{
			ft_putstr_fd("Minishell : exit : too many arguments\n", 2);
			return (p->exit_status = 1, 1);
		}
	}
	if (node->options[1])
	{
		if (validate_argument(p, node->options[1]) != 0)
			return (1);
		exit_status = ft_atold(node->options[1]);
	}
	else
		exit_status = p->exit_status;
	ft_putstr_fd("exit\n", 2);
	exit(exit_status % 256);
}
