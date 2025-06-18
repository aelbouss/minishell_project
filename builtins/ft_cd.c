#include "../minishell.h"

char	*get_env_value(t_data_shell *p, t_env *eh, char *env_name)
{
	char	*env_value;
       
	if (!eh || !p || !env_name)
		return (NULL);
	while (eh)
	{
		if (ft_strcmp(eh->name, env_name) == 0)
		{
			if (eh ->value)
			{
				env_value = ft_strdup(p, eh->value);
				if (!env_value)
					return (NULL);
				return(env_value);
			}
		}
		eh = eh->next;
	}
	return (NULL);
}

int	modify_env_var(t_data_shell *p , t_env *lst, char *name, char *newvalue)
{

	if (!p || !name || !newvalue)
		return (1);
	while (p)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (lst->value)
			{
				lst->value = NULL;
				lst->value = s_strdup(p, newvalue);
				if (!lst->value)
					return (printf("Bad Allocation\n"), 1);
				return (0);
			}
			else
				return (perror("empty env variable\n") , 1);
		}
		lst = lst->next;
	}
	return (1);
}

int prev_path_case(t_data_shell *p, t_env *env_lst)
{
	char	*old_pwd;
	char	*curr_dir;
	char	*prev;

	old_pwd = s_strdup(p, get_env_value(p, env_lst, "PWD"));
	if (!old_pwd)
		return (perror("Bad Allocation\n"), 1);
	prev = get_env_value(p, env_lst, "OLDPWD");
	if (chdir(prev) != 0)
		return (printf("Minishell : cd %s:  No such file or directory\n", prev),p->exit_status = 1, 1);
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("Bad Allocation\n"), 1);
	if (modify_env_var(p, env_lst, "OLDPWD", old_pwd) != 0)
		return (perror("Error : failed  to change OLDPWD\n"), p->exit_status = 1, 1);
	if (modify_env_var(p, env_lst, "PWD", curr_dir) != 0)
		return (perror("Error : failed  to change  PWD\n"), p->exit_status = 1, 1);
	return (0);
}

int	ft_cd(t_data_shell *p, t_env *env_lst ,char *path)
{
	char	*old_pwd;
	char	*curr_dir;

	if (!path || !p)
		return (1);
	if (ft_strcmp(path, "-") == 0)
	{
		if (prev_path_case(p, env_lst) != 1)
		{
			p->exit_status = 1;
			return (1);
		}
		return (0);
	}
	old_pwd = s_strdup(p, get_env_value(p, env_lst, "PWD"));
	if (!old_pwd)
		return (perror("Bad Allocation\n"), 1);
	if (chdir(path) != 0)
		return (printf("Minishell : cd %s:  No such file or directory\n", path),p->exit_status = 1, 1);
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("Bad Allocation\n"), 1);
	if (modify_env_var(p, env_lst, "OLDPWD", old_pwd) != 0)
		return (perror("Error : failed  to change OLDPWD\n"), p->exit_status = 1, 1);
	if (modify_env_var(p, env_lst, "PWD", curr_dir) != 0)
		return (perror("Error : failed  to change  PWD\n"), p->exit_status = 1, 1);
	//free(curr_dir);
	return (0);
}