#include "../minishell.h"

int		__check_is_dir__(t_data_shell *p ,char *path)
{
	struct	stat infos;

	stat(path, &infos);
	if (S_ISDIR(infos.st_mode))
	{
		printf("Minishell : %s : is a directory\n", path);
		p->exit_status = 126;
		return (1);
	}
	return (0);
}

void	wait_for_child(pid_t pid, t_data_shell *p)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		p->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		p->exit_status = 128 + WTERMSIG(status);
}

int		__check_permission(t_data_shell *p, char *path)
{
	if (access(path, W_OK | R_OK  | X_OK) != 0)
	{
		printf("minishell : %s : permission denied \n", path);
		p->exit_status = 126;
		fg_free_gc(&p->fgc);
		free_gc(&p->line.head);
		return (1);
	}
	return (0);
}