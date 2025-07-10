/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:00:58 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 17:25:39 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nbr_len(int n)
{
	int	cnt;

	if (n == 0)
		return (1);
	cnt = 0;
	while (n != 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

int	check_if_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*s_itoa(int n)
{
	int			len;
	char		*ptoc;
	long int	nbr;

	nbr = (long int)n;
	len = nbr_len(n);
	if (check_if_negative(nbr) == 1)
	{
		nbr = nbr * -1;
		len += 1;
	}
	ptoc = malloc(len + 1 * sizeof(char));
	if (ptoc == NULL)
		return (NULL);
	if (nbr_len(nbr) == 1)
		ptoc[0] = '0';
	ptoc[len--] = '\0';
	if (check_if_negative(n) == 1)
		ptoc[0] = '-';
	while (nbr != 0)
	{
		ptoc[len--] = (nbr % 10 + '0');
		nbr /= 10;
	}
	return (ptoc);
}

void	default_setup(t_data_shell *mshell)
{
	mshell->line.head = NULL;
	mshell->exit_status = 0;
	mshell->env_list = NULL;
	mshell->nc = 0;
	mshell->r_sign = 0;
	mshell->pwd = NULL;
}

void	shell_lvl_handling(t_data_shell *mshell)
{
	int		nbr;
	char	*s_nbr;
	char	*gnbr;

	s_nbr = get_env_value(mshell->env_list, "SHLVL");
	if (s_nbr)
	{
		nbr = ft_atoi(s_nbr);
		nbr++;
		free(s_nbr);
		gnbr = s_itoa(nbr);
		if (gnbr)
		{
			modify_env_var(mshell->env_list, "SHLVL", gnbr);
			free(gnbr);
		}
	}
}
