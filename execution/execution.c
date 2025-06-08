#include "../minishell.h"

int	**open_pipes(t_data_shell *p)
{
	int	**pipes;
	int	i;

	pipes = gc_malloc(((p->nc) * sizeof(int *)), &p->line.head);
	if (!pipes)
		return (perror("Bad A llocation\n"), NULL);
	i = 0;
	while(i < p->nc - 1)
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

	if(!pipes)
		return ;
	i = 0;
	while(pipes[i])
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
