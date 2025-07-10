/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:37:51 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 00:26:06 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data_shell *p)
{
	char	*wdir;

	wdir = get_env_value(p->env_list, "PWD");
	if (!wdir)
	{
		wdir = getcwd(NULL, 0);
		if(!wdir)
		{
			wdir = p->pwd;
			printf("%s\n", wdir);
			p->exit_status = 0;
			return(0);
		}
		printf("%s\n", wdir);
		free(wdir);
		p->exit_status = 0;
		return (0);
	}
	printf("%s\n", wdir);
	free(wdir);
	p->exit_status = 0;
	return (0);
}
