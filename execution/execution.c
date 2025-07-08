/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:13:52 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/08 20:23:33 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**open_pipes(t_data_shell *p)
{
	int	**pipes;
	int	i;

	pipes = gc_malloc(((p->nc) * sizeof(int *)), &p->line.head);
	if (!pipes)
		return (perror("Bad A llocation\n"), NULL);
	i = 0;
	while (i < p->nc - 1)
	{
		pipes[i] = gc_malloc(2 * sizeof(int), &p->line.head);
		if (!pipes[i])
			return (NULL);
		i++;
	}
	pipes[i] = NULL;
	i = 0;
	while (pipes[i])
	{
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), NULL);
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	handle_pipes(int np, int **pipes, int idx)
{
	if (idx == 0)
	{
		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
			return (perror("dup2-1"), 1);
	}
	else if (idx == np)
	{
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2-2"), 1);
	}
	else
	{
		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
	}
	close_pipes(pipes);
	return (0);
}

void	setup_utils(t_data_shell *mshell, char **envp, t_exec *container)
{
	if (!mshell)
		exit(1);
	default_setup(mshell);
	if (envp[0])
		create_env_list(mshell, envp);
	else
		secondary_env_list(mshell);
	shell_lvl_handling(mshell);
	mshell->exec = container;
}

void	create_minimal_envs(t_data_shell *mshell)
{
	t_env	*node1;
	t_env	*node2;
	t_env	*node3;

	node1 = build_node("SHLVL=1");
	if (!node1)
		return ;
	add_to_linkedlist(&mshell->env_list, node1);
	node2 = build_node("_=/usr/bin/env");
	if (!node2)
		return ;
	add_to_linkedlist(&mshell->env_list, node2);
	node3 = build_node("OLDPWD");
	if (!node3)
		return ;
	add_to_linkedlist(&mshell->env_list, node3);
	node3->flag = 1;
}
