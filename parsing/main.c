/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/11 19:08:32 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac,char **av ,char **envp)
{
	t_minishell	a;

	(void)ac ;
	(void)av;
	create_env_list(&a, envp);
	while (1)
	{
		printf("SHELL[%s]",getcwd(NULL, 0));
		a.line.rl = readline(" : ");
		if (!a.line.rl)
			return (1);
        if (check_syntax(&a, &a.line, &a.list,envp) != 0)
			break ;
		if (ft_loop_and_exec(&a) != 0)
		     break ;
	}
}
