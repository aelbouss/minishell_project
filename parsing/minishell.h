/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:03:34 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/11 19:08:50 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h> 
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>


typedef enum    s_types
{
    PIPE,
    HEREDOC,
    INPUT,
    APPEND,
    OVERWRITE,
    WORD,  
    RFILE,
    EXPAND,
}               t_types;

typedef struct s_gc // template of  the  garbage  collector 
{
    void    *add;
    struct s_gc *next;
}              t_gc;

// 'typedef struct s_chi7aja
// {
//     char    *lex;
//     size_t  size_lex;
//     t_types lex_type;
// }   t_lex;'

typedef struct s_token //template for create  tokens
{
    t_types type;
    char *line;
    struct s_token *next;
}               t_token;

typedef struct s_cmd
{
    char    *rl; //readed line 
    t_gc    *head; // add head for garbage collector
    t_token  *token_list;
}              t_cmd;

typedef struct s_redr
{
    char *str;
    char *file;
    t_types type;
    struct s_redr *next;
}               t_redr;

typedef struct s_cline // last list  that  contain  commands and list  of  >> | 
{
    char **options; // "ls -la"
    t_redr  *r_list; // the  list  that  contain  the  redirection .
    struct s_cline *next;
}               t_cline;

typedef struct s_env // template  of  envs 
{
    char *name;
    char *value;
    struct s_env *next;
}               t_env;

typedef struct s_exec // the template  of  the  execution .
{
    char    **ep; // environment pointer.
    int     es; // exit status.
    char    **sp; // splited path
    char    *path;
}   t_exec;

typedef struct s_minishell // the  tempale  that  combine all  the  struct .
{
    t_cmd line;
    t_cline *list;
    t_exec  *execution; // pointer  for  execution  struct .
    t_env   *env_head; //pointer  for list of  envs
    t_env   *ul;
}               t_minishell;

size_t				ft_strlen(const char *s);
void    *gc_malloc(size_t allocate, t_gc **list);
void    add_to_list(t_gc **list,t_gc *node);
t_gc    *ft_gc_new(void *ptr);
void    free_gc(t_gc **list);
void    token_line(t_cmd *file);
int check_syntax(t_minishell *mshell,t_cmd *line, t_cline **list, char **env);
void    making_list( t_cmd *file, t_cline **list);

//env prototypes
void	add_to_linkedlist(t_env **lst, t_env *new);
t_env	*build_node(t_minishell *p, char *str);
int	split_each_env(char *s, char **name, char **value, t_minishell *p);
char	*extract_name(char *s, t_minishell *p);
char	*extract_value(char *s, t_minishell *p);
void	create_env_list(t_minishell *p, char **envp);

//builtins
char	*get_env_value(t_minishell *p, t_env *eh, char *env_name);
int ft_cd(t_minishell *p, char *path);
int	modify_env_var(t_env *p, char *name, char *newvalue);
int	ft_cd(t_minishell *p, char *path);
int	ft_echo(t_minishell *p, char **args);
int	ft_pwd(t_minishell *p);

//execution
char	*get_path_env(char **ep) ;
char	**extract_splited_path(char *path);
void	clean_2d_array(char **arr);
char	*join_and_free(char	**sp, char *s2, int i);
char	*check_executable(char **sp, char **incmd);
int loking_for_builtins(t_minishell *p);
int	ft_loop_and_exec(t_minishell *p);

#endif
