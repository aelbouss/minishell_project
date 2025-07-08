/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:36:45 by aelbouss          #+#    #+#             */
/*   Updated: 2025/06/30 21:38:39 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data_shell *p)
{
	t_env	*ptr;

	ptr = p->env_list;
	if (!ptr)
		return (perror("env() failed\n"), 1);
	while (ptr)
	{
		if (ptr->flag == 0)
		{
			if (ptr->name)
				printf("%s", ptr->name);
			if (ptr->value)
				printf("=%s", ptr->value);
			printf("\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
