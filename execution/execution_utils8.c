/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:16:01 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/09 01:11:46 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_2d_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

void	close_fds(t_data_shell *p, int fd)
{
	close(p->fds[0]);
	close(p->fds[1]);
	close(fd);
}

void	perr_exit(char *keyword, t_data_shell *p , int fd)
{
	puterr(keyword);
	close(fd);
	close(p->fds[0]);
	close(p->fds[1]);
	exit(0);
}

void	close_fds_exit(t_data_shell *mshell, int fd)
{
	close_fds(mshell, fd);
	exit(0);
}

void	sub_free(char *old_pwd, char *prev)
{
	if (old_pwd)
		free(old_pwd);
	if (prev)
		free(prev);
}