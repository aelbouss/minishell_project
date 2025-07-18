/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:18:26 by memahamo          #+#    #+#             */
/*   Updated: 2025/07/12 18:22:48 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = 0;
	if (validate_name(name) != 0)
	{
		free(name);
		return (put_err(str), NULL);
	}
	return (name);
}

char	**extract_identifier_and_value(t_data_shell *p, char *str)
{
	char	**arr;

	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = get_name(str);
	if (!arr[0])
		return (clear_2d_arr(arr), p->exit_status = 1, NULL);
	arr[1] = extract_value(str);
	arr[2] = NULL;
	return (arr);
}

int	check_if_exists(t_env *lst, char *name)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	numeric_string(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) != 2048)
			return (1);
		i++;
	}
	return (0);
}
