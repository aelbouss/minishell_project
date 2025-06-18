/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/17 19:59:25 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data_shell	mshell;
	t_exec	container;
	int	fd_i;
	int	fd_o;
	
	((void)ac), ((void)av);
	mshell.line.head = NULL; 
	mshell.exit_status = 0;
	mshell.fgc = NULL;
	mshell.env_list = NULL;
	mshell.nc = 0;
	create_env_list(&mshell, env);
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
			add_history(mshell.line.rl);
			if (check_syntax(&mshell, &mshell.line, &mshell.list) != 1)
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

// notes  for  the  project 
/*
	- check how  the  builtins and  heardoc work  in  bash .
	- check cd , tests removing  PWD , OLDPWD.
	- loop  trough all  an  open  all the  heardocs  .
*/