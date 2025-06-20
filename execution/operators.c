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


int	handle_operators(t_data_shell *p  ,t_redr *operator, char	**commands)
{
	int	fd;

	if (!operator || !commands)
		return (1);
	while(operator)
	{
		if (ft_strcmp(operator->str, ">") == 0)
		{
			if (redirection_out(operator->file, commands) != 0)
				return (1);
			p->r_sign = 1;
		}
		else if (ft_strcmp(operator->str, "<") == 0)
		{
			if (redirection_in(operator->file) != 0)
				return (1);
			p->r_sign = 1;
		}
		else if(ft_strcmp(operator->str, ">>") == 0)
		{
			if (append_to(operator->file, commands) != 0)
				return (1);
			p->r_sign = 1;
		}
		else if(ft_strcmp(operator->str, "<<") == 0)
		{
			fd = open(operator->f_path, O_RDWR);
			if (fd < 0)
				return (perror("error"), 1);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("dup2"), 1);
			p->r_sign = 1;
			close(fd);
		}
		operator = operator->next;
	}
	return (0);
}