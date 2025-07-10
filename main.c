/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:31:18 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data_shell	mshell;
	t_exec			container;

	((void)ac), ((void)av);
	setup_utils(&mshell, env, &container);
	while (1)
	{
		apply_signals(&mshell);
		mshell.line.rl = readline("MINISHELL : ");
		after_read(&mshell);
		if (mshell.line.rl)
		{
			if (*mshell.line.rl)
				add_history(mshell.line.rl);
			if (check_syntax(&mshell, &mshell.line, &mshell.list) != 1)
				loop_and_execute(mshell.list, env, &mshell);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			return (clear_ressources(&mshell), 0);
		}
		clear_garbage(&mshell);
	}
	return (mshell.exit_status);
}
