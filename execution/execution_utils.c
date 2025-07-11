/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:42:37 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/11 22:41:44 by aelbouss         ###   ########.fr       */
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

	if (!path || !cmd || cmd[0] == '\0' || !p)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (check_permission(p, cmd) != 0)
		{
			clear_ressources(p);
			close(p->fds[0]);
			close(p->fds[1]);
			exit(126);
		}
	}
	tmp = ft_strjoin(p, path, "/");
	if (!tmp)
		return (perror("Bad Allocation\n"), NULL);
	fcmd = ft_strjoin(p, tmp, cmd);
	if (!fcmd)
		return (perror("Bad Allocation\n"), NULL);
	return (fcmd);
}

char	*check_if_exe(char **envp, char **cmd, t_data_shell *p)
{
	int		i;
	char	*fcmd;

	if (!envp || !cmd || cmd[0] == 0 || !p)
		return (NULL);
	p->exec->gep = turn_list_to_arr(p->env_list, p);
	if (!p->exec->gep)
		return (NULL);
	verify_if_access_path(cmd, p->exec->gep, p);
	p->exec->path = extract_path_env(p->exec->gep);
	if (!p->exec->path)
		return (NULL);
	p->exec->sp = get_splited_path(p->exec->path, p);
	if (!p->exec->sp)
		return (NULL);
	i = 0;
	while (p->exec->sp[i])
	{
		fcmd = build_absolute_path(p->exec->sp[i++], cmd[0], p);
		if (!fcmd)
			return (NULL);
		if (access(fcmd, X_OK) == 0)
			return (fcmd);
	}
	return (NULL);
}

int	execute_exe(char **cmd, char **envp, t_data_shell *p)
{
	int		pid;
	char	*fcmd;

	if (!envp || !p)
		return (1);
	if (!cmd || !*cmd)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_DFL);
		if (check_is_dir(p, cmd[0]) != 0)
			faileur(126, p);
		fcmd = check_if_exe(envp, cmd, p);
		if (!fcmd)
			error_case(cmd, p);
		execve(fcmd, cmd, p->exec->gep);
		execve_fail(p);
	}
	else
		wait_for_child(pid, p);
	return (0);
}
