#include "../minishell.h"

int	bi_redirection_in(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("error"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("error"), 1);
	return (0);
}



void	handle_bi_operations(t_redr *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (ft_strcmp(lst->str, ">") == 0)
			//handle >
		else if (ft_strcmp(lst->str, ">>") == 0)
			//handle  append >>
		else if (ft_strcmp(lst->str, "<") == 0)
			//handle in <
		else if (ft_strcmp(lst->str, "<<") == 0)
			// handle  heardoc;
		lst = lst ->next;
	}
}

int	reduplicate_to_origin(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (perror("error"),1);
	return (0);
}