/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:07:00 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/10 19:49:33 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	after_read(t_data_shell *mshell)
{
	if (g_exit_status == 130)
		mshell->exit_status = g_exit_status;
}

void	apply_signals(t_data_shell *mshell)
{
	(void)mshell;
	g_exit_status = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
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
