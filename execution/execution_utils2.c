#include "../minishell.h"

int	one_cmd(t_data_shell *p, t_cline *lst, char **envp)
{
	if (!p || !lst)
		return (1);
	if (heardoc_heandler(p, p->list) != 0)
		return (1);
	while (lst)
	{
		handle_operators(p, lst->r_list, lst->options);
		if (check_is_builtin(lst, p, p->env_list) != 0)
		{
			execute_exe(lst->options, envp, p);
		}
		lst = lst->next;
	}
	return (0);
}

int	core_process(t_data_shell *p,  char **envp, t_cline *lst, int **aop, int i)
{
	char	*fcmd;

	if (!p || !*lst->options)	
		exit (1);
    if (handle_pipes(p->nc - 1, aop, i) != 0)
            exit(1);
    if (check_is_builtin(lst, p, p->env_list) != 0)
    {
        fcmd = check_if_exe(envp, lst->options[0], p);
        if(fcmd)
            execute_exe(lst->options, envp, p);
        else
		{
        	printf("(%s) : command not found\n", lst->options[0]);
			clear_ressources(p);
			exit (127);
		}
    }
	clear_ressources(p);
    exit(0);
}
void	count_her(t_data_shell *mshell)
{
	t_cline *tmp1;
	t_redr *tmp2;
	int count;

	count = 0;
	tmp1 = mshell->list;
	while(tmp1)
	{
		tmp2 = tmp1->r_list;
		while(tmp2)
		{
			if(tmp2->type == 1)
				count++;
			if (count >16)
			{
				ft_putstr_fd("max  here-docs  is  16\n", 2);
				free_gc(&(mshell->line.head));
				fg_free_gc(&(mshell->fgc));
				exit(2);
			}
			tmp2 = tmp2->next;		
		}
		tmp1 = tmp1->next;
	}
}

void	_wait_childs_(pid_t	*pids, t_data_shell *p)
{
	int		i;
	int		status;

	if (!pids || ! p)
		return ;
	i = 0;
	while (i < p->nc)
	{
		 waitpid(pids[i], &status, 0);
		if (i == p->nc - 1)
   		{
        	if (WIFEXITED(status))
            	p->exit_status = WEXITSTATUS(status);
        	else if (WIFSIGNALED(status))
            	p->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	main_process(t_data_shell *p, t_cline *lst, char **envp)
{
	int		pid;
	int		*pids;
	int		**aop;
	int		i;

	aop = open_pipes(p);
	if (!aop)
        return (perror("Bad Allocation\n"), 1);
    pids = gc_malloc((sizeof(pid_t) * p->nc), &p->line.head);
	i = 0;
	while(lst)
    {
		handle_operators(p, lst->r_list, lst->options);
        pid = fork();
		if (pid < 0)
			return (perror ("fork failed"), 1);
        if (pid == 0)
			core_process(p, envp, lst ,aop, i);
        else if (pid > 0)
            pids[i++] = pid;
        lst = lst->next;
    }
	 close_pipes(aop);
	_wait_childs_(pids, p);
	return (0);
}

int many_commands(t_data_shell *p, t_cline *lst, char **envp)
{
    if (!p || !lst || !lst->options)
        	return (1);
	heardoc_heandler(p, p->list);
	main_process(p, lst, envp);
    return (0);
}

int	loop_and_execute(t_cline *lst, char **envp, t_data_shell *p)
{
	int fd_i;
	int fd_o;

	fd_i = dup(STDIN_FILENO);
	fd_o = dup(STDOUT_FILENO);
	count_her(p);
	p->nc = list_len(lst);
	if (p->nc > 1)
		many_commands(p, lst, envp);
	else
		one_cmd(p, lst, envp);
	if (p->r_sign != 0)
	{
		dup2(fd_i,STDIN_FILENO);
		dup2(fd_o,STDOUT_FILENO);
		p->r_sign = 0;
	}
	return (0);
}

void	clear_ressources(t_data_shell *p)
{
	free(p->line.rl);
	free_gc(&p->line.head);
	fg_free_gc(&p->fgc);
}
