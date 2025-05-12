#include "../minishell.h"

void	ft_escape_cautes(int *p, char **args, int i)
{
	int	j;

	j = 0;
	while(args[i][j] && (args[i][j] == '"' || args[i][j] == '\''))
		j++;
	p[0] = j;
	j = ft_strlen(args[i]) - 1;
	while (j >= 0 && (args[i][j] == '"' || args[i][j] == '\''))
		j--;
	p[1] = j;
}

int	ft_find_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			retunr (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_minishell *p, char **args)
{
	int	i;
	int	j;
	int	arr[2];

	if (!p || !args || !args[1])
		return (printf("\n"), 0);
	i = 1;
	if (ft_find_char())
		i++;
	while (args[i])
	{
		ft_escape_cautes(arr, args, i);
		j = arr[0];
		while (args[i][j] && j <= arr[1])
		{
			printf("%c",args[i][j]);
			j++;
		}
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
	return (0);
}
