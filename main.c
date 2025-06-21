/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/21 16:30:58 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{
	t_data_shell	mshell;
	t_exec			container;
	
	((void)ac), ((void)av);
	__setup_utils__(&mshell, env, &container);
	while (1)
	{
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
	}
	return (0);
}