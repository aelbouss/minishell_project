/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:48:37 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/20 21:27:18 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_gc    *ft_gc_new(void *ptr) // create new node and  add  inside  it the  allocated  block
{
    t_gc *list;

    list = malloc(sizeof(t_gc));
    if (!list)
        return NULL;
    else
    {
        list->add = ptr;
        list->next = NULL;
    }
    return list;
}

void    add_to_list(t_gc **list,t_gc *node) // add  the  node  to  the  list 
{
    t_gc    *tmp;

    if (!list || !(*list))
        *list = node;
    else
    {
        tmp = *list;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
}

void    *gc_malloc(size_t allocate, t_gc **list) // allocate in a pointer to add it to the list
{
    void *tmp;

    tmp = malloc(allocate);
    if (!tmp)
        return NULL;
    add_to_list(list,ft_gc_new(tmp));
    return tmp;
}

void    free_gc(t_gc **list) // goiong  trough the  list  and  free .
{
    t_gc *tmp;

    tmp = *list;
    while ((*list))
    {
        *list = (*list)->next;
        if (tmp->add)
            free(tmp->add);
        free(tmp);
        tmp = (*list);
    }
    list = NULL;
}