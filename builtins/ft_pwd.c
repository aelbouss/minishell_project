/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:37:51 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/05 20:28:12 by memahamo         ###   ########.fr       */
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
		printf("%s\n", wdir);
		free(wdir);
		return (0);
	}
	printf("%s\n", wdir);
	////////free wdir
	free(wdir);
	return (0);
}
// save  the  PWD inside  a variable .