/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:59:11 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/05 20:31:24 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_case(char **cmd, t_data_shell *p)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(cmd[0], 2);
	write(2, "\n", 1);
	clear_ressources(p);
	close(p->fds[0]);
	close(p->fds[1]);
	exit(127);
}

int	list_cnt(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	file_opener(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC);
	if (fd < 0)
		return (perror("open"), 1);
	return (fd);
}

int	is_here_doc(t_data_shell *p, t_redr *operator)
{
	int		fd;

	fd = open(operator->f_path, O_RDWR);
	if (fd < 0)
		return (perror("open"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), 1);
	p->r_sign = 1;
	close(fd);
	return (0);
}

void	execve_fail(t_data_shell *p)
{
	perror("execve");
	p->exit_status = 127;
	exit(1);
}
