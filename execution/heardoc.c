#include  "../minishell.h"

int	heardoc(char *keyword)
{
	char	*line;
	int	fd[2];
	char	*fl;

	if (!keyword)
		return (1);
	if (pipe(fd) == -1)
		return (perror("error"), 1);
	while (1)
	{
		line = readline("heardoc> ");
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			return (perror("Bad Allocation\n"), 1);
		}
		if (ft_strcmp(keyword, line) == 0)
		{
			close(fd[1]);
			break ;
		}
		fl = ft_strjoin(line, "\n");
		if (!fl)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		write(fd[1], fl, ft_strlen(fl));
		free(line);
	}
	dup2(fd[0], STDIN_FILENO);
	//close (fd[0])
	return (0);
}
