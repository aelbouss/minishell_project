/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:07:00 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/28 15:51:55 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}


void	apply_signals(t_data_shell *mshell)
{
	g_exit_status = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (g_exit_status == 130)
		mshell->exit_status = g_exit_status;
}

void	handler_2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

void	prompt_synchronisation(int exit)
{
		if (exit == 130)
			printf("\n");
		if (exit == 131)
			printf("quit\n");
}