/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:32:17 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 17:02:22 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_builtin(t_cline *node, t_data_shell *p, t_env *lst)
{
	if (!p || !node || !node->options || !node->options[0])
		return (1);
	if (ft_strcmp(node->options[0], "cd") == 0)
		return (ft_cd(p, lst, node->options), 0);
	if (ft_strcmp(node->options[0], "env") == 0)
		return (ft_env(p), 0);
	if (ft_strcmp(node->options[0], "export") == 0)
		return (ft_export(p, node), 0);
	if (ft_strcmp(node->options[0], "echo") == 0)
		return (ft_echo(node->options, p), 0);
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

int	print_envs(t_env *lst, t_data_shell *p)
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
			printf("\"%s\"", lst->value);
		}
		printf("\n");
		lst = lst->next;
	}
	p->exit_status = 0;
	return (0);
}

int	home_path(t_data_shell *p, t_env *env_lst)
{
	char	*old_pwd;
	char	*curr_dir;
	char	*home_path;

	old_pwd = get_env_value(env_lst, "PWD");
	home_path = get_env_value(env_lst, "HOME");
	if (!home_path)
	{
		if (old_pwd)
			free(old_pwd);
		ft_putstr_fd("Minishell : cd : Home not set\n", 2);
		return (p->exit_status = 1, 1);
	}
	chdir(home_path);
	free(home_path);
	p->exit_status = 0;
	curr_dir = getcwd(NULL, 0);
	if (modification_process(env_lst, old_pwd, curr_dir) != 0)
		return (1);
	return (0);
}
