#include "../minishell.h"

char	*get_env_value(t_minishell *p, t_env *eh, char *env_name)
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
				env_value = ft_strdup(eh->value);
				if (!env_value)
					return (NULL);
				return(env_value);
			}
		}
		eh = eh->next;
	}
	return (NULL);
}

int	modify_env_var(t_env *p, char *name, char *newvalue)
{

	if (!p || !name || !newvalue)
		return (1);
	while (p)
	{
		if (ft_strcmp(p->name, name) == 0)
		{
			if (p->value)
			{
				free(p->value);
				p->value = NULL;
				p->value = ft_strdup(newvalue);
				if (!p->value)
					return (printf("Bad Allocation\n"), 1);
				return (0);
			}
			else
				return (perror("empty env variable\n") , 1);
		}
		p = p->next;
	}
	return (1);
}

int	ft_cd(t_minishell *p, char *path)
{
	char	*old_pwd;
	char	*curr_dir;

	if (!path || !p)
		return (1);
	old_pwd = ft_strdup(get_env_value(p, p->env_head, "PWD"));
	if (!old_pwd)
		return (perror("Bad Allocation\n"), 1);
	if (chdir(path) != 0)
		return (perror("Error"), 1);
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("Bad Allocation\n"), 1);
	if (modify_env_var(p->env_head, "OLDPWD", old_pwd) != 0)
		return (perror("Error : failed  to change OLDPWD\n"), 1);
	if (modify_env_var(p->env_head, "PWD", curr_dir) != 0)
		return (perror("Error : failed  to change  PWD\n"), 1);
	free(old_pwd);
	free(curr_dir);
	return (0);
}
