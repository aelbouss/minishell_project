/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/05 15:08:10 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data_shell	mshell;
	t_exec	container;
	int	fd_i;
	int	fd_o;

	create_env_list(&mshell, env);
	((void)ac), ((void)av);
	mshell.line.head = NULL; 
	mshell.exit_status = 0;
	mshell.exec = &container;
	fd_i = dup(STDIN_FILENO);
	fd_o = dup(STDOUT_FILENO);
	while (1)
	{
		mshell.r_sign = 0;
		apply_signals(&mshell);
		mshell.line.rl = readline("MINISHELL : ");
		if (mshell.line.rl)
		{
			check_syntax(&mshell, &mshell.line, &mshell.list);
			add_history(mshell.line.rl);
			loop_and_execute(mshell.list, env, &mshell);
		}
		else
		{
			free_gc(&mshell.line.head);
			return (5200);
		}
		free(mshell.line.rl);
		free_gc(&mshell.line.head);
		if (mshell.r_sign != 0)
		{
			dup2(fd_i,STDIN_FILENO);
			dup2(fd_o,STDOUT_FILENO);
		}
	}
	return (0);
}
