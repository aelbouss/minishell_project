#include "../minishell.h"

// |||||||||||||||||||| utils  needed  for  execution .

// get path env ;

char	*extract_path_env(char **envp)
{
	char	*path;
	int		i;

	path = "PATH=/";
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], path, 6) == 0)
			return(envp[i]);
		i++;
	}
	return (NULL);
}

// get the splited  path

char	**get_splited_path(char *path, t_data_shell *p)
{
	char	**sp;

	sp = s_split(p, path, ':');
	if (!sp)
		return (NULL);
	return (sp);
}

// join cmd with  /

char	*build_absolute_path(char *path, char *cmd, t_data_shell *p)
{
	char	*fcmd;
	char	*tmp;

	if (!path || !cmd || !p)
		return (NULL);
	tmp = ft_strjoin(p, path, "/");
	if (!tmp)
		return (perror("Bad Allocation\n"), NULL);
	fcmd = ft_strjoin(p, tmp, cmd);
	if (!fcmd)
		return (perror("Bad Allocation\n"), NULL);
	return (fcmd);
}

// check if  executable

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

int	execute_exe(char **cmd, char **envp , t_data_shell *p)
{
	int	pid;
	int	status;
	char	*fcmd;

	if (!cmd || !envp || ! p)
		return(perror("Bad Address\n"), 1);
	fcmd = check_if_exe(envp, cmd[0], p);
	if (!fcmd)
		return (printf("%s not found\n",cmd[0]),1);
	pid = fork();
	if (pid == 0)
	{
		execve(fcmd, cmd, p->exec->gep);
		return(perror("perror"), 1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			p->exit_status = WEXITSTATUS(status);
	}
	return (0);
}