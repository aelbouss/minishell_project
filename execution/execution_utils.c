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

	sp = _split(path, ':');
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

char	*concat_and_free(char*s1, char *s2)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(s1, "=");
	if (!str1)
		return (perror("Bad Allocation\n"), NULL);
	str2 = ft_strjoin(str1, s2);
		if (!str2)
		return (perror("Bad Allocation\n"), NULL);
	free(str1);
	return(str2);
}

char	**turn_list_to_arr(t_env *lst, t_minishell *p)
{
	int	i;
	char	**arr;
	t_env	*tmp;

	if (!lst || !p)
		return (perror("Bad Allocation\n") ,NULL);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	arr = gc_malloc((sizeof(char *) * i), &p->line.head);
	if (!arr)
		return (perror("Bad Allocation\n"), NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = concat_and_free(lst->name, lst->value); 
		if (!arr[i-1])
			return (perror("Bad Allocation"), NULL);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}