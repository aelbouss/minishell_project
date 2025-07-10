/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:35:41 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 16:40:22 by aelbouss         ###   ########.fr       */
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
			if (eh->value)
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
	if (!lst || !name || !newvalue)
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

int	prev_path_case(t_data_shell *p, t_env *env_lst)
{
	char	*old_pwd;
	char	*curr_dir;
	char	*prev;

	if (!p || !env_lst)
		return (1);
	old_pwd = get_env_value(env_lst, "PWD");
	prev = get_env_value(env_lst, "OLDPWD");
	if (!prev)
	{
		sub_free(old_pwd, prev);
		return (ft_putstr_fd("Minishell : cd : OLDPWD not set\n", 2), 1);
	}
	chdir(prev);
	free(prev);
	p->exit_status = 0;
	curr_dir = getcwd(NULL, 0);
	if (modification_process(env_lst, old_pwd, curr_dir) != 0)
		return (1);
	return (0);
}

int	prev_dir(t_data_shell *p, t_env *env_lst)
{
	if (prev_path_case(p, env_lst) != 1)
	{
		p->exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(t_data_shell *p, t_env *env_lst, char **path)
{
	char	*old_pwd;
	char	*curr_dir;

	if (!p || !env_lst)
		return (1);
	if (path[1] && path[2])
	{
		ft_putstr_fd("Minishell : cd : too many arguments\n", 2);
		return (p->exit_status = 1, 1);
	}
	if (!path[1])
		return (home_path(p, env_lst), 0);
	if (ft_strcmp(path[1], "-") == 0)
		return (prev_dir(p, env_lst), 0);
	old_pwd = get_env_value(env_lst, "PWD");
	if (chdir(path[1]) != 0)
		return (change_dir_fail(p, old_pwd, path[1]), 1);
	p->exit_status = 0;
	if (p->pwd)
		free(p->pwd);
	p->pwd = s_strdup(path[1]);
	curr_dir = getcwd(NULL, 0);
	if (modification_process(env_lst, old_pwd, curr_dir) != 0)
		return (1);
	return (0);
}
