/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:35:41 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/08 20:30:10 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *eh, char *env_name)
{
	char	*env_value;

	if (!eh || !env_name)
		return (NULL);
	while (eh)
	{
		if (ft_strcmp(eh->name, env_name) == 0)
		{
			if (eh ->value)
			{
				env_value = s_strdup(eh->value);
				if (!env_value)
					return (NULL);
				return (env_value);
			}
		}
		eh = eh->next;
	}
	return (NULL);
}

int	modify_env_var(t_env *lst, char *name, char *newvalue)
{
	if (!lst ||!name || !newvalue)
		return (1);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (lst->value)
				free(lst->value);
			lst->value = NULL;
			lst->value = s_strdup(newvalue);
			if (!lst->value)
				return (perror("Bad Allocation\n"), 1);
			lst->flag = 0;
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

int	prev_path_case(t_env *env_lst)
{
	char	*old_pwd;
	char	*curr_dir;
	char	*prev;

	old_pwd = s_strdup(get_env_value(env_lst, "PWD"));
	if (!old_pwd)
		return (perror("Bad Allocation\n"), 1);
	prev = get_env_value(env_lst, "OLDPWD");
	if (chdir(prev) == -1)
		return (printf("Minishell : cd  - :  No such file or directory\n"), 1);
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("Bad Allocation\n"), 1);
	if (modify_env_var(env_lst, "OLDPWD", old_pwd) != 0)
		return (1);
	if (modify_env_var(env_lst, "PWD", curr_dir) != 0)
		return (free(curr_dir), 1);
	free(curr_dir);
	return (0);
}

int	prev_dir(t_data_shell *p, t_env *env_lst)
{
	if (prev_path_case(env_lst) != 1)
	{
		p->exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(t_data_shell *p, t_env *env_lst, char *path)
{
	char	*old_pwd;
	char	*curr_dir;

	if (!p)
		return (1);
	if (!path)
		return (home_path(p, env_lst), 0);
	if (ft_strcmp(path, "-") == 0)
		return (prev_dir(p, env_lst), 0);
	old_pwd = get_env_value(env_lst, "PWD");
	if (!old_pwd)
		return (1);
	if (chdir(path) != 0)
		return (printf("Minishell : cd %s:  No such file or directory\n", path),
			p->exit_status = 1, 1);
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("Bad Allocation\n"), 1);
	if (modify_env_var(env_lst, "OLDPWD", old_pwd) != 0)
		return (free(old_pwd), 1);
	free(old_pwd);
	if (modify_env_var(env_lst, "PWD", curr_dir) != 0)
		return (free(curr_dir), 1);
	free(curr_dir);
	return (0);
}
