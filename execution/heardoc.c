#include  "../minishell.h"

int	heardoc(char *keyword)
{
	char	*line;
	int	fd[2];


	if (!keyword)
		return (1);
	if (pipe(fd) == -1)
		return (perror("error"), 1);
	while (1)
	{
		line = readline("heardoc> ");
		if (!line || ft_strcmp(keyword, line) == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close (fd[0]);
			return (0);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n" , 1);
		free(line);
	}
	return (1);
}
