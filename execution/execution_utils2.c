#include "../minishell.h"

int	one_cmd(t_data_shell *p, t_cline *lst, char **envp)
{
	char	*fcmd;

	if (!p || !lst || !lst->options)
		return (1);
	while (lst)
	{
		handle_operators(p, lst->r_list, lst->options);
		if (check_is_builtin(lst, p, p->env_list) != 0)
		{
			fcmd = check_if_exe(envp, lst->options[0], p);
			if(fcmd)
				execute_exe(lst->options, envp, p);
			else
				return (printf("%s : not found\n", lst->options[0]),1);
		}
		lst = lst->next;
	}
	return (0);
}

int	loop_and_execute(t_cline *lst, char **envp, t_data_shell *p)
{
	p->nc = list_len(p->list);
	if (p->nc > 1)
	{
		// more commands
		printf("\nhhhhhhhhhhhh\n");
	}
	else
	{
		one_cmd(p, lst, envp);
	}
	return (0);
}