#include "../minishell.h"

int	looking_for_char(char *s, int n)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != n)
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **args)
{
	int	i;

	if (!args || !args[1])
		return (printf("\n"), 0);
	i = 1;
	while(args[i])
	{
		if (args[i][0] == '-' && looking_for_char(args[i],'n') == 0)
			i++;
		else
			break ;
	}
	while (args[i])
	{
		printf("%s",args[i]);
		if (i > 0)
			printf(" ");
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
	return (0);
}
