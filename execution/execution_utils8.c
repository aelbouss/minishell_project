/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:16:01 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/04 19:04:34 by aelbouss         ###   ########.fr       */
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

/*void	loking_for_heredoc()
{
	if (ft_strcmp(operator->str, "<<") == 0)
	{
		if (is_here_doc(p, operator) != 0)
			return (1);
		return (p->r_sign = 1, 0);
	}
}
*/