/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:47:04 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/11 22:38:07 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	one_cmd(t_data_shell *p, t_cline *lst, char **envp)
{
	if (!p || !lst)
		return (1);
	if (heardoc_heandler(p, p->list) != 0)
		return (1);
	while (lst)
	{
		if (handle_operators(p, lst->r_list, lst->options) != 0)
			return (1);
		if (check_is_builtin(lst, p, p->env_list) != 0)
		{
			execute_exe(lst->options, envp, p);
		}
		lst = lst->next;
	}
	return (0);
}

int	core_process(t_data_shell *p, char **envp, t_cline *lst, int i)
{
	if (!p || !*lst->options)
		exit(1);
	(void)i ;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_DFL);
	if (check_is_builtin(lst, p, p->env_list) != 0)
		execute_exe(lst->options, envp, p);
	clear_ressources(p);
	close(p->fds[0]);
	close(p->fds[1]);
	exit(0);
}

void	count_her(t_data_shell *mshell)
{
	t_cline	*tmp1;
	t_redr	*tmp2;
	int		count;

	count = 0;
	tmp1 = mshell->list;
	while (tmp1)
	{
		tmp2 = tmp1->r_list;
		while (tmp2)
		{
			if (tmp2->type == 1)
				count++;
			if (count > 16)
			{
				ft_putstr_fd("max  here-docs  is  16\n", 2);
				clear_ressources(mshell);
				exit(2);
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	_wait_childs_(pid_t *pids, t_data_shell *p)
{
	int	i;
	int	status;

	if (!pids || !p)
		return ;
	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < p->nc)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			p->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			p->exit_status = 128 + WTERMSIG(status);
			prompt_synchronisation(p->exit_status);
		}
		i++;
	}
}

int	main_process(t_data_shell *p, t_cline *lst, char **envp)
{
	int	pid;
	int	*pids;
	int	i;

	p->aop = open_pipes(p);
	if (!p->aop)
		return (perror("Bad Allocation\n"), 1);
	pids = gc_malloc((sizeof(pid_t) * p->nc), &p->line.head);
	i = 0;
	while (lst)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork failed"), 1);
		if (pid == 0)
			child_behaviour(p, i, envp, lst);
		else if (pid > 0)
			pids[i++] = pid;
		lst = lst->next;
	}
	close_pipes(p->aop);
	_wait_childs_(pids, p);
	return (0);
}
