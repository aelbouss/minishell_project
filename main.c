/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/23 19:35:30 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac,char **av ,char **envp)
{
	t_minishell	a;
	t_minishell *p;
	int	o_in;
	int	o_out;

	(void)ac ;
	(void)av;
	p = &a;
	create_env_list(p, envp);
	while (1)
	{
		o_in = dup(STDIN_FILENO);
		o_out = dup(STDOUT_FILENO);
		printf("\nSHELL[%s]",getcwd(NULL, 0));
		p->line.rl = readline(" : ");
		if (!p->line.rl)
			return (1);
        if (check_syntax(p, &p->line, &p->list, envp) != 0)
			break ;
		if (ft_loop_and_exec(p, p->env_head) != 0)
		    break ;
		dup2(o_out, 1);
		dup2(o_in, 0);
	}
	return (0);
}
