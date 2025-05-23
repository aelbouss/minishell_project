#include "../minishell.h"

int	redirection_out(char *file)
{
	int	fd;

	if (!file)
		return (1);
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

int	append_to(char *file)
{
	int	fd;

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