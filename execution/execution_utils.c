/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:42:37 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/02 22:27:45 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_path_env(char **envp)
{
	char	*path;
	int		i;

	path = "PATH=/";
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], path, 6) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	**get_splited_path(char *path, t_data_shell *p)
{
	char	**sp;

	sp = s_split(p, path, ':');
	if (!sp)
		return (NULL);
	return (sp);
}

char	*build_absolute_path(char *path, char *cmd, t_data_shell *p)
{
	char	*fcmd;
	char	*tmp;

	if (!path || !cmd || !p)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (__check_permission(p, cmd) != 0)
		{
			clear_ressources(p);
			exit(126);
		}
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	tmp = ft_strjoin(p, path, "/");
	if (!tmp)
		return (perror("Bad Allocation\n"), NULL);
	fcmd = ft_strjoin(p, tmp, cmd);
	if (!fcmd)
		return (perror("Bad Allocation\n"), NULL);
	return (fcmd);
}

char	*check_if_exe(char **envp, char *cmd, t_data_shell *p)
{
	int		i;
	char	*fcmd;

	if (!envp || !cmd || !p)
		return (NULL);
	p->exec->gep = turn_list_to_arr(p->env_list, p);
	if (!p->exec->gep)
		return (NULL);
	p->exec->path = extract_path_env(p->exec->gep);
	if (!p->exec->path)
		return (NULL);
	p->exec->sp = get_splited_path(p->exec->path, p);
	if (!p->exec->sp)
		return (NULL);
	i = 0;
	while (p->exec->sp[i])
	{
		fcmd = build_absolute_path(p->exec->sp[i], cmd, p);
		if (!fcmd)
			return (NULL);
		if (access(fcmd, X_OK) == 0)
			return (fcmd);
		i++;
	}
	return (NULL);
}

int	execute_exe(char **cmd, char **envp, t_data_shell *p)
{
	int		pid;
	char	*fcmd;

	if (!envp || ! p)
		return (perror("Bad Address\n"), 1);
	if (!cmd || !*cmd)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (__check_is_dir__(p, cmd[0]) != 0)
			faileur(126, p);
		fcmd = check_if_exe(envp, cmd[0], p);
		if (!fcmd)
			error_case(cmd, p);
		execve(fcmd, cmd, p->exec->gep);
		execve_fail(p);
	}
	else
		wait_for_child(pid, p);
	return (0);
}
