#include "../minishell.h"

int	redirection_out(char *file, char **commands)
{
	int	fd;

	if (!file)
		return (1);
	if (!commands)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC ,  0664);
		if (fd < 0)
			return (perror("error"), 1);
		return (0);
	}
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC ,  0664);
	if (fd < 0)
		return (perror("error"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("error"), 1);
	close (fd);
	return (0);
}

int	redirection_in(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("error"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("error"), 1);
	close(fd);
	return (0);
}

int	append_to(char *file, char	**commands)
{
	int	fd;

	if (!commands)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC ,  0664);
		if (fd < 0)
			return (perror("error"), 1);
		return (0);
	}
	fd = open(file, O_CREAT | O_RDWR | O_APPEND ,  0664);
	if (fd < 0)
		return (perror("error"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("error"), 1);
	close (fd);
	return (0);
}


int	operator_handler(t_data_shell *p, t_redr *operator, char **commands)
{
	if (ft_strcmp(operator->str, ">") == 0)
	{
			if (redirection_out(operator->file, commands) != 0)
				return (p->r_sign = 1, 1);
			return (0);
	}
	else if (ft_strcmp(operator->str, "<") == 0)
	{
			if (redirection_in(operator->file) != 0)
				return (p->r_sign = 1, 1);
			return (0);
	}
	else if(ft_strcmp(operator->str, ">>") == 0)
	{
			if (append_to(operator->file, commands) != 0)
				return (p->r_sign = 1, 1);
			return (0);
	}
	else if(ft_strcmp(operator->str, "<<") == 0)
	{	
			if (is_here_doc(p, operator) != 0)
				return (p->r_sign = 1, 1);
			return (0);
	}
	return (1);
}

int	handle_operators(t_data_shell *p  ,t_redr *operator, char	**commands)
{
	if (!operator || !commands)
		return (1);
	while(operator)
	{
		operator_handler(p, operator, commands);
		operator = operator->next;
	}
	return (0);
}
