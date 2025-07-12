#include "../minishell.h"

int execute_child(char **cmd, char **envp, t_data_shell *p)
{
	char	*fcmd;

	if (!envp || !p)
		return (1);
	if (!cmd || !*cmd)
		return (0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_DFL);
	if (check_is_dir(p, cmd[0]) != 0)
		faileur(126, p);
	fcmd = check_if_exe(envp, cmd, p);
	if (!fcmd)
	error_case(cmd, p);
	execve(fcmd, cmd, p->exec->gep);
	execve_fail(p);
    return(0);
}