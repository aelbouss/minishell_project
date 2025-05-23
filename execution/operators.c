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


int	reduplicate_streams(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		return (perror("error:"), 1);
	if (dup2(out, STDIN_FILENO) == -1)
		return (perror("error:"), 1);
	close(in);
	close(out);
	return (0);
}

int	is_builtin(char *str)
{
	if (!str)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (0);
	else if (ft_strcmp(str, "echo") == 0)
		return (0) ;
	else if (ft_strcmp(str, "pwd") == 0)
		return (0);
	else if (ft_strcmp(str, "export") == 0)
		return (0);
	else if (ft_strcmp(str, "env") == 0)
		return (0);
	else if (ft_strcmp(str, "unset") == 0)
		return (0);
	else if (ft_strcmp(str, "exit") == 0)
		return (0);
	return (1);
}