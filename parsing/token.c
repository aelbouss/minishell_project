/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:25:20 by memahamo          #+#    #+#             */
/*   Updated: 2025/04/30 16:31:14 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//////////////////////////////////////////
// Skips characters until the second quote
//////////////////////////////////////////

void    search_second_quotes(char *line, char c, int *i, int *len)
{
    (*i)++;
    (*len)++;
    printf("%d - ",*i);
    while (line[*i])
    {
        if (line[*i] == c && (line[*i +1] == '\0' || line[*i +1] == ' ' || line[*i +1] == '\t' 
        || line[*i +1] == '<' || line[*i +1] == '>' || line[*i +1] == '|' 
        || line[*i +1] == '\"' ||  line[*i +1] == '\'' ))
        {
            (*i)++;
            (*len)++;            
            break;
        }
        (*i)++;
        (*len)++;
    }

}
//////////////////////////////////////////////////////////////////////////////
// Counts the length of the next token starting from a given index in the line
//////////////////////////////////////////////////////////////////////////////

int count_line(char *line, int i)
{
    int len;

    len = 0;
    while (line[i] && line[i] != ' ' && line[i] != '\t') 
    {
        if (line[i] == '\'')
            search_second_quotes(line, '\'', &i, &len);
        else if (line[i] == '\"')
        {
            search_second_quotes(line, '\"', &i, &len);
        }
        else if (line[i] != '<' && line[i] != '>' && line[i] != '|')
        {
           ((i)++), (len++);
        }
        else
            break;
    }
    return len;
}
////////////////////////////////////////
// chose the type (|, redirections ,...)
////////////////////////////////////////

void    chose_type(t_token **new)
{
    if (ft_strcmp((*new)->line,"|") == 0)
        (*new)->type = PIPE;
    else if (ft_strcmp((*new)->line,"<<") == 0)
        (*new)->type = HEREDOC;
    else if (ft_strcmp((*new)->line,">>") == 0)
        (*new)->type = APPEND;
    else if (ft_strcmp((*new)->line,"<") == 0)
        (*new)->type = OVERWRITE;
    else if (ft_strcmp((*new)->line,">") == 0)
        (*new)->type = INPUT;
    else
        (*new)->type = WORD;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Creates a new token with the given length from the input line, adds it to the token list
///////////////////////////////////////////////////////////////////////////////////////////

void    add_token(t_cmd *file ,int *i, int len)
{
    t_token *new;
    
    new = gc_malloc(sizeof(t_token), &file->head);
    if (!new)
        return ;
    else
    {
        new->line = ft_substr(file->rl, *i, len);
        add_to_list(&(file->head),ft_gc_new(new->line));
        *i += len;
        chose_type(&new);
        //printf("in a_t : (%s) , its  type  is (%d)\n",new->line, new->type);
        new->next = NULL;
        if (file->token_list == NULL )
            file->token_list = new;
        else
        {
            t_token *tmp ;
            tmp = file->token_list;
            while (tmp->next)
            {   
                tmp = tmp->next;
            }
            tmp->next = new;
        }
    }
}
//////////////////////////
///token line : split line
//////////////////////////

void    token_line(t_cmd *file) // tokenize the  line  and  add  it to  list
{
    int i;

    i = 0;
    file->token_list = NULL;
    while(file->rl[i])
    {
        if (ft_strncmp(&(file->rl[i]),"|",1) == 0)
            add_token(file, &i,1);
        else if (ft_strncmp(&(file->rl[i]),"<<",2) == 0)
            add_token(file, &i, 2);
        else if (ft_strncmp(&(file->rl[i]),">>",2) == 0)
            add_token(file, &i, 2);
        else if (ft_strncmp(&(file->rl[i]),"<",1) == 0)
            add_token(file, &i, 1);
        else if (ft_strncmp(&(file->rl[i]),">",1) == 0)
            add_token(file, &i, 1);
        else if (file->rl[i] != ' ' && file->rl[i] != '\t')
            add_token(file,&i, count_line(file->rl,i));
        else
            i++;          
    }
    // t_token *tmp;
    // tmp = (file->token_list);
    // while(tmp)
    // {
    //     printf("type : %d | line : %s\n",tmp->type,tmp->line);
    //     tmp = tmp->next;
    // }
}

