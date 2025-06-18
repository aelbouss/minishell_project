#include "../minishell.h"


int	heardoc(t_data_shell *mshell,  char *keyword)
{
	char	*line;
	int	fd[2];
	int sfd;


	if (!keyword)
		return (1);
	if (pipe(fd) == -1)
		return (perror("error"), 1);
	while (1)
	{
		line = readline("heardoc> ");
		if (!line || ft_strcmp(keyword, line) == 0)
		{
/////
		}
		if( ft_strchr(line, '$') != NULL && (ft_strchr(keyword, '\'') != NULL || ft_strchr(keyword, '"') != NULL))
			line = her_fcts(mshell, line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n" , 1);
		///line filel
		free(line);
	}
	return (sfd);
}
