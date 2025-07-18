/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:27:10 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/11 22:38:16 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_garbage(t_data_shell *p)
{
	free(p->line.rl);
	free_gc(&p->line.head);
}

void	child_behaviour(t_data_shell *p, int i, char **envp, t_cline *lst)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_DFL);
	if (handle_pipes(p->nc - 1, p->aop, i) != 0)
		exit(1);
	if (handle_operators(p, lst->r_list, lst->options) != 0)
		exit(1);
	core_process(p, envp, lst, i);
}

void	access_cmd(char **cmd, char **envp, t_data_shell *p)
{
	if (!cmd)
		return ;
	execve(cmd[0], cmd, envp);
	execve_fail(p);
}

void	put_err(char *str)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : non valid identifier\n", 2);
}

int	check_path(t_data_shell *p, char **path)
{
	struct stat	infos;

	if (stat(path[1], &infos) != 0)
		return (0);
	if (!S_ISDIR(infos.st_mode))
	{
		ft_putstr_fd(path[1], 2);
		ft_putstr_fd(" : not a directory\n", 2);
		p->exit_status = 1;
		return (1);
	}
	if (access(path[1], X_OK) != 0)
	{
		ft_putstr_fd("Minishell : cd : ", 2);
		ft_putstr_fd(path[1], 2);
		ft_putstr_fd(" : permission  denied\n", 2);
		p->exit_status = 1;
		return (1);
	}
	if (path[1] && path[2])
	{
		ft_putstr_fd("Minishell : cd : too many arguments\n", 2);
		return (p->exit_status = 1, 1);
	}
	return (0);
}
