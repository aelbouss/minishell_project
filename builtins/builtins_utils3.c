/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 03:56:05 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/11 22:29:58 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	modification_process(t_env *env_lst, char *old_pwd, char *curr_dir)
{
	if (old_pwd)
	{
		if (modify_env_var(env_lst, "OLDPWD", old_pwd) != 0)
			return (free(old_pwd), free(curr_dir), 1);
		free(old_pwd);
	}
	if (curr_dir)
	{
		if (modify_env_var(env_lst, "PWD", curr_dir) != 0)
			return (free(curr_dir), 1);
		free(curr_dir);
	}
	return (0);
}

void	change_dir_fail(t_data_shell *p, char *old_pwd, char *path)
{
	if (old_pwd)
		free(old_pwd);
	ft_putstr_fd("Minishell : cd : ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	p->exit_status = 1;
	return ;
}

void	signals_heredoc(void)
{
	signal(SIGINT, handler_2);
	signal(SIGQUIT, SIG_IGN);
}

void	close_fds_a(t_data_shell *p)
{
	close(p->fds[0]);
	close(p->fds[1]);
}

void	verify_if_access_path(char **arg, char **envp, t_data_shell *p)
{
	if (!p || !envp || !arg)
		return ;
	if (arg[0][0] != '/' && arg[0][0] != '.')
		return ;
	if (access(arg[0], F_OK | X_OK) == 0)
		access_cmd(arg, envp, p);
	else
	{
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		close_fds_a(p);
		clear_ressources(p);
		exit(127);
	}
}
