/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:37:51 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/03 16:02:46 by aelbouss         ###   ########.fr       */
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
	return (0);
}
// save  the  PWD inside  a variable .