#include "../minishell.h"

int	count_nodes(t_cline *lst)
{
	int	i;

	printf("heree");
	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}
int	**open_pipes(int np, t_minishell *p)
{
	int	**pipes;
	int	i;

	pipes = gc_malloc((((np + 1)* sizeof(int *))), &p->line.head);
	if (!pipes)
		return (NULL);
	i = 0;
	while(i < np)
	{
		pipes[i] = gc_malloc(2 * sizeof(int), &p->line.head);
		if (!pipes[i])
			return (perror("Bad Allocation\n"), NULL);
		i++;
	}
	pipes[i] = NULL;
	i = 0;
	while (pipes[i])
	{
		if (pipe(pipes[i]) == -1)
			return(perror("Bad Allocation\n"), NULL);
		i++;
	}
	return (pipes);
}


void	close_pipes(int **arr, int np)
{
	int	i;

	i = 0;
	while (i < np)
	{
		close(arr[i][0]);
		close(arr[i][1]);
		i++;
	}
}