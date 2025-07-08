/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:32:17 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/05 18:54:59 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_builtin(t_cline *node, t_data_shell *p, t_env *lst)
{
	if (!p || !node || !node->options || !node->options[0] || !lst)
		return (1);
	if (ft_strcmp(node->options[0], "cd") == 0)
		return (ft_cd(p, lst, node->options[1]), 0);
	if (ft_strcmp(node->options[0], "env") == 0)
		return (ft_env(p), 0);
	if (ft_strcmp(node->options[0], "export") == 0)
		return (ft_export(p, node), 0);
	if (ft_strcmp(node->options[0], "echo") == 0)
		return (ft_echo(node->options), 0);
	if (ft_strcmp(node->options[0], "pwd") == 0)
		return (ft_pwd(p), 0);
	if (ft_strcmp(node->options[0], "unset") == 0)
		return (ft_unset(p, &p->env_list, node), 0);
	if (ft_strcmp(node->options[0], "exit") == 0)
		return (ft_exit(node, p), 0);
	return (1);
}

int	search_for_char(char *s, int n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == n)
			return (1);
		i++;
	}
	return (0);
}

int	print_envs(t_env *lst)
{
	while (lst)
	{
		if (lst->name)
		{
			printf("declare -x ");
			printf("%s", lst->name);
		}
		if (lst->value)
		{
			printf("=");
			printf("%s", lst->value);
		}
		printf("\n");
		lst = lst -> next;
	}
	return (0);
}

int	is_valid_identifier(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c == '_'))
		return (0);
	return (1);
}

int	home_path(t_data_shell *p, t_env *env_lst)
{
	char	*old_pwd;
	char	*curr_dir;
	char	*home_path;

	old_pwd = get_env_value(env_lst, "PWD");
	home_path = get_env_value(env_lst, "HOME");
	if (chdir(home_path) == -1)
	{
		if (old_pwd)
			free(old_pwd);
		return (printf("Minishell : cd : Home not set\n"),
			p->exit_status = 1, 1);
	}
	curr_dir = getcwd(NULL, 0);
	if (old_pwd)
	{
		if (modify_env_var(env_lst, "OLDPWD", old_pwd) != 0)
		return (1);
		free(old_pwd);
	}
	if (curr_dir)
	{
		if (modify_env_var(env_lst, "PWD", curr_dir) != 0)
			return (free(curr_dir), 1);
		free(curr_dir);
	}
	free(home_path);
	return (0);
}
