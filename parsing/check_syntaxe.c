/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:15:31 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/20 21:27:11 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

////////////////////////////////////////////////////////////////////////
// Checks if all quotes (single and double) in the input line are closed
////////////////////////////////////////////////////////////////////////
int    check_quotes(t_cmd *line)
{
    int i;

    i = 0;
    while(line->rl[i])
    {
        if (line->rl[i] == '\'')
        {
            i++;
            if (ft_strchr_copy((line->rl),'\'',&i) == 1) // check if exists just one (')
                return 1;
            else
                i++;
        } 
        else if (line->rl[i] == '\"' ) // check if exists just one (")
        {
            i++;
            if (ft_strchr_copy((line->rl),'\"',&i) == 1)
                return 1;
            else
                i++;
        }
        else
            i++;
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Validates pipe ('|'), rediretcions syntax:the command doesn't start or end with a pipe and redirections are placed correctly
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_validate_syntax(t_cmd *file)
{
    t_token *tmp;

    tmp = file->token_list;
    if (tmp->type == 0)
        return 1;
    while (tmp->next)
    {
        if ((tmp->type != 0 && tmp->type != 5) && tmp->next->type != 5)
            return 1;
        tmp = tmp->next;
    }
    if (tmp->type != 5)
        return 1;
    else
        return 0;

}
/////////////////////////////////
/// add nodes to env limked list
//////////////////////////////// 

void    add_nodes_list(t_minishell *mshell,char **strs)
{
    t_env *new;

    new = gc_malloc(sizeof(t_env), &(mshell->line.head));
    if (new == NULL)
        return;
    new->name = strs[0];
    new->value = strs[1];
    new->next = NULL;
    if (mshell->env_head == NULL)
        mshell->env_head = new;
    else
    {
        t_env *tmp;
        
        tmp = mshell->env_head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
/////////////////
// creat env list
/////////////////
void env_list(t_minishell *mshell, char **env)
{
    char **strs;
    int i;
    
    i = 0;
    mshell->env_head = NULL;
    while (env[i])
    {  
        strs = NULL;
        strs = ft_split(env[i], '=');
        add_nodes_list(mshell,strs);
        i++;
    }
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// check syntax (quotes and pipes), builds the command ( tokrn list) and environment linked lists
/////////////////////////////////////////////////////////////////////////////////////////////////

int check_syntax(t_minishell *mshell, t_cmd *line, t_cline **list, char **env)
{
    (void)mshell;
    (void)env;
    if (line->rl)
    {
        if (check_quotes(line) == 1 )  // check "" , '
        {
            printf("error\n");
            free_gc(&(line->head));
        }
        else
        {
            line->token_list = NULL;
            token_line(line);
            if (check_validate_syntax(line) == 1)
            {
                printf("error\n");
                free_gc(&(line->head));
                return (1);
            }
            else 
            {    
                making_list(line, list);
               //env_list(mshell,env); 
            }
        }
    }    
    return 0;
}

                // t_cline *tmp;
                // tmp = *list;
                // int i = 0;
                // t_redr *t1 ;
                // while(tmp)
                // {
                //     t1 = tmp->r_list;
                //     i = 0;
                //     // printf(" ==== %s \n",&tmp->options[3]);
                //     while(tmp && tmp->options[i] != 0)
                //     {
                //         printf("i = %i | option  s: %s\n",i,tmp->options[i]);
                //         i++;
                //     }
                //     printf("redrictions \n");
                //     while(t1)
                //     {
                //         printf("r : %s type : %u file : %s\n",t1->str , t1->type,t1->file);
                //         t1 = t1->next;
                //     }
                //     printf("next node \n");
                //     tmp = tmp->next;
                // }
