#include "../minishell.h"

char	*get_path_env(char **ep) // get the path environement varable
{
	int	i;
	char	*path;

	if (!ep || !*ep)
		return (NULL);
	path = "PATH=/";
	i = 0;
	while (ep[i])
	{
		if (ft_strncmp(path, ep[i], 6) == 0)
			return (ep[i]);
		i++;
	}
	return (NULL);
}

char	**extract_splited_path(char *path) //split  the  path
{
	char	**sp; // splitted path

	sp = ft_split(path, ':');
	if (!sp)
		return (NULL);
	free(path);
	return (sp);
}

void	clean_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

char	*join_and_free(char	**sp, char *s2, int i) // concat each path with the  command like  /usr/bin/command
{
		char	*tmp;
		char	*cmd;

		tmp = ft_strjoin(sp[i], "/");
		if (!tmp)
		{
			clean_2d_array(sp);
			return (NULL);
		}
		cmd = ft_strjoin(tmp, s2);
		if (!cmd)
		{
			free(tmp);
			clean_2d_array(sp);
			return (NULL);
		}
		return (cmd);
}

char	*check_executable(char **sp, char **incmd)  // test  all  exe paths with  the  command and  test each one
{
	char	*cmd;
	int	i;

	if (!sp || !*sp)
		return (NULL);
	i = 0;
	while (sp[i])
	{
		cmd = join_and_free(sp, incmd[0], i);
		if (!cmd)
		{
			ft_putstr_fd("Bad Allocation\n", 2);
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
		{
			clean_2d_array(sp);
			return (cmd);
		}
	}
	printf("command : %s not  found",incmd[0]);
	return (NULL);
}
