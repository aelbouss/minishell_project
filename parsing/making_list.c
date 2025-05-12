/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:05:41 by memahamo          #+#    #+#             */
/*   Updated: 2025/04/29 16:38:57 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
////////////////////////////////////////////////////////////////////////
// select the files for redirections , allocate memory to char **options
////////////////////////////////////////////////////////////////////////

void    making_word(t_cmd *file, t_cline *list)
{
    t_token *tmp;
    int len;
    
    tmp = file->token_list;
    len = 0;
    while (tmp && tmp->type != 0)
    {
        if (tmp->type != 5 && tmp->next &&  tmp->next->type == 5)
        {
            tmp->next->type = RFILE;
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    tmp = file->token_list;
    while (tmp && tmp->type != 0)
    {
        if (tmp->type == 5)
            len++;
        tmp = tmp->next;
    }
    list->options = gc_malloc(sizeof(char *) * (len +1), &(file->head));
}
///////////////////////
// add noddes to cline 
///////////////////////

void    add_nodes(t_cmd *file, t_cline **list, t_cline **new)
{
    *new = gc_malloc(sizeof(t_cline), &(file->head));
    if(!new)
        return ;
    if (list == NULL || *list == NULL)
    {
        *list = *new;
        (*list)->next = NULL;
    }
    else
    {
        t_cline *tmp; 
        tmp = *list;
        while(tmp->next )
        {   
            tmp = tmp->next;
        }
        tmp->next = *new;
    } 
}
/////////////////////////////////////////
// making the linked list of redirections 
/////////////////////////////////////////

void    making_red_list(t_cmd *file, t_token *tmp, t_redr **new)
{
    t_redr *node;
    
    node = gc_malloc(sizeof(t_redr), &file->head);
    if (!node)
        return;
    if (*new == NULL)
        *new = node;
    else
    {
        t_redr *tmp;
        tmp = *new;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
    node->str = tmp->line;
    node->type = tmp->type;
    node->file = tmp->next->line;
    node->next = NULL;
}
/////////////////////////////////////////////////////////////////
///split token for each node : options char **, list redirections
/////////////////////////////////////////////////////////////////
void    split_line(t_cmd *file, t_token **tmp, t_cline **new)
{
    int i;
    
    i = 0;
    making_word(file,*new);
    (*new)->r_list = NULL;
    while (*tmp && (*tmp)->type != 0)
    {
        if ((*tmp)->type != 5)
        {
            making_red_list(file, *tmp,&((*new)->r_list));
            *tmp = (*tmp)->next;   
        }
        else if ((*tmp)->type == 5)
            (*new)->options[i++] =( *tmp)->line;
        *tmp = (*tmp)->next;
    }  
    (*new)->options[i] = NULL;
}
////////////////
// create node 
//////////////////////
void    making_list(t_cmd *file, t_cline **list)
{
    t_token *tmp;
    t_cline *new;

    *list = NULL;
    tmp = file->token_list;
    while (tmp)
    {
        if (tmp->type != 0) 
        {            
            add_nodes(file,list,&new);
            split_line(file, &tmp, &new);
        }
        else
            tmp = tmp->next; 
        new->next = NULL;   
    } 
}
