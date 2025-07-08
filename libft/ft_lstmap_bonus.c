/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:57:59 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/22 10:33:20 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*str;
	t_list	*tmp;
	void	*content_tmp;

	str = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		content_tmp = f(lst->content);
		tmp = ft_lstnew(content_tmp);
		if (tmp == NULL)
		{
			del(content_tmp);
			ft_lstclear(&str, del);
			return (NULL);
		}
		ft_lstadd_back(&str, tmp);
		lst = lst->next;
	}
	return (str);
}
