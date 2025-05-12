#include "../minishell.h"

int	loking_for_builtins(t_minishell *p)
{
	if (ft_strcmp(p->list->options[0], "cd") == 0)
	{
		ft_cd(p, p->list->options[1]);
		return (0);
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
	/*
	if (ft_strncmp(p->list->options, "export") == 0)
		ft_export(); // still missed
	if (ft_strncmp(p->list->options, "unset") == 0)
		ft_unset(); // still missed
	if (ft_strncmp(p->list->options, "env") == 0)
		ft_env(); // still missed
	if (ft_strncmp(p->list->options, "exit") == 0)
		ft_exit(); // still missed
	if (ft_strncmp(p->list->options, "pwd") == 0)
		ft_pwd();
	*/
	else
		return (1);
	return (0);
}

int	ft_loop_and_exec(t_minishell *p)
{
	//pid_t	pid;
	//int	status;

	if (!p || !p->list || !p->list->options)
		return (1);
	while (p->list)
	{
		if (loking_for_builtins(p) == 1)
		{
			/*
			pid = fork();
			if (pid == 0)
			{
				execve(p->list->options[0],p->list->options, NULL);
				perror("execve() failed\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
				{
					p->execution->es = WEXITSTATUS(status);
					printf("the exit status of the child is : %d\n", p->execution->es);
				}
			}
			*/
			printf("invalid command\n");
		}
		p->list = p->list->next;
	}
	return (0);
}

