/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:00:25 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/23 15:10:42 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac,char **av ,char **envp)
{
	t_minishell	a;
	t_minishell *p;

	(void)ac ;
	(void)av;
	p = &a;
	create_env_list(p, envp);
	while (1)
	{
		printf("\nSHELL[%s]",getcwd(NULL, 0));
		p->line.rl = readline(" : ");
		if (!p->line.rl)
			return (1);
        if (check_syntax(p, &p->line, &p->list, envp) != 0)
			break ;
		if (ft_loop_and_exec(p, p->env_head) != 0)
		    break ;
		
	}
	return (0);

}
