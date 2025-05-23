#include "../minishell.h"

int	initialize_utils(t_exec *exe, t_minishell *p, t_env *lst)
{
	p->execution->gep = turn_list_to_arr(lst, p);
	if (!p->execution->gep)
		return(perror("Bad Allocation1\n"), 1);
	exe->path = get_path_env(p->execution->gep);
	if (!exe->path)
		return (3);
	exe->sp = _split(exe->path, ':');
	if (!exe->sp)
		return (perror("Bad Allocation2\n"), 1);
	free(exe->path);
	return (0);
}

char	*extract_executable(char *cmd, t_exec *exec)
{
	int		i;
	char	*subcmd;
	char	*fcmd;

	i = 0;
	while(exec->sp[i])
	{
		subcmd = ft_strjoin(exec->sp[i], "/");
		if (!subcmd)
			return (perror("Bad Allocation\n"), NULL);
		fcmd = ft_strjoin(subcmd, cmd);
		if (!fcmd)
			return (perror("Bad Allocation\n"), NULL);
		if (access(fcmd, X_OK) == 0)
		{
			free(subcmd);
			return (fcmd);
		}
		i++;
	}
	return (NULL);
}

int	loking_for_executables(t_minishell *p , t_env *lst)
{
	t_exec	exec;
	char	*cmd;
	pid_t	pid;
	int	status;

	if (!p || !lst)
		return (1);
	p->execution = &exec;
	if (initialize_utils(&exec, p, lst) == 1)
		return (perror("Bad Allocation\n"), 1);
	cmd = extract_executable(p->list->options[0], &exec);
	if (!cmd)
		return (printf("%s : not found\n",p->list->options[0]), 1);
	pid = fork();
	if (pid == 0)
	{
		if (p->list->r_list)
			if (handle_operators(p->list->r_list) != 0)
				return (1);
		execve(cmd, p->list->options, p->execution->gep);
		perror("execve() failed\n");
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			p->execution->es = WEXITSTATUS(status);
	}
	return (0);
}

int	loking_for_builtins(t_minishell *p)
{
	if (ft_strcmp(p->list->options[0], "cd") == 0)
	{
		return(ft_cd(p, p->list->options[1]), 0);
	}
	if (ft_strcmp(p->list->options[0], "echo") == 0)
	{
		ft_echo(p, p->list->options);
		return (0);
	}
	if (ft_strcmp(p->list->options[0], "pwd") == 0)
	{
		ft_pwd(p);
		return (0);
	}
	if (ft_strcmp(p->list->options[0], "export") == 0)
	{
		ft_export(p);
		return (0);
	}
	if (ft_strcmp(p->list->options[0], "env") == 0)
	{
		ft_env(p);
		return (0);
	}
	if (ft_strcmp(p->list->options[0], "unset") == 0)
	{
		if (ft_unset(p,&p->env_head) == 1)
			printf("errrrrrrrrrrrrrrrrrrrrrrrrrr\n");
		return (0);
	}
	if (ft_strcmp(p->list->options[0], "exit") == 0)
	{
		ft_exit(p);
		return (0);
	}
	else
		return (1);
	return (0);
}

int handle_operators(t_redr *operator)
{
	if (!operator)
		return (1);
	while(operator)
	{
		if (ft_strcmp(operator->str, ">") == 0)
		{
			if (redirection_out(operator->file) != 0)
				return (1);
		}
		else if (ft_strcmp(operator->str, "<") == 0)
		{
			if (redirection_in(operator->file) != 0)
				return (1);
		}
		else if(ft_strcmp(operator->str, ">>") == 0)
		{
			if (append_to(operator->file) != 0)
				return (1);
		}
		else if (ft_strcmp(operator->str, "<<") == 0)
		{
			if (heardoc(operator->file) != 0)
				return (1);
		}
		operator = operator->next;
	}
	return (0);
}

int	ft_loop_and_exec(t_minishell *p, t_env *lst)
{
	//pid_t	pid;
	//int	status;

	if (!p || !p->list || !p->list->options)
		return (1);
	while (p->list)
	{
		/*if (handle_operators(p->list->r_list) != 0)
			return (1);*/
		if (loking_for_builtins(p) == 1)
			loking_for_executables(p, lst);
		p->list = p->list->next;
	}
	return (0);
}

