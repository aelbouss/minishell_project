/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/28 21:00:48 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data_shell	mshell;

	((void)ac), ((void)av);
	mshell.line.head = NULL;
	mshell.exit_status = 0;
	while (1)
	{
		apply_signals(&mshell);
		mshell.line.rl = readline("MINISHELL : ");
		if (mshell.line.rl)
		{
			check_syntax(&mshell, &mshell.line, &mshell.list, env);
			add_history(mshell.line.rl);
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
