/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:03:34 by memahamo          #+#    #+#             */
/*   Updated: 2025/05/28 21:27:58 by memahamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
// #include "../minishell / libft.h "

typedef enum s_types
{
	PIPE,
	HEREDOC,
	OUTPUT,
	APPEND,
	INPUT,
	WORD,
	RFILE,
	EXPAND,
}					t_types;

typedef struct s_gc
{
	void			*add;
	struct s_gc		*next;
}					t_gc;

// 'typedef struct s_chi7aja
// {
//     char    *lex;
//     size_t  size_lex;
//     t_types lex_type;
// }   t_lex;'

typedef struct s_token
{
	t_types			type;
	char			*line;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*rl;
	t_gc			*head;
	t_token			*token_list;
}					t_cmd;

typedef struct s_redr
{
	char			*str;
	char			*file;
	int				ambiguous;
	t_types			type;
	struct s_redr	*next;
}					t_redr;

typedef struct s_cline
{
	char			**options;
	t_redr			*r_list;
	int				is_true;
	int				len_options;
	int				index_1;
	int				index_2;
	struct s_cline	*next;
}					t_cline;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data_shell
{
	t_cmd			line;
	t_cline			*list;
	t_env			*env_list;
	int				exit_status;
}					t_data_shell;

typedef struct s_exp_info
{
	char			**expand_result;
	int				j;
	int				count_word;
	char			*mdf_option;
	char			*return_fnct;
}					t_exp_info;

//////////////////////////// libft ////////////////////////////

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *nptr);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strdup(t_data_shell *mshell, const char *s);
void				*ft_calloc(t_data_shell *mshell, size_t nmemb, size_t size);
char				*ft_substr(t_data_shell *mshell, char const *s,
						unsigned int start, size_t len);

char				*ft_strtrim(t_data_shell *mshell, char const *s1,
						char const *set);
char				**ft_split(t_data_shell *mshell, char const *s, char c);
char				*ft_itoa(t_data_shell *mshell, int n, int *j);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strchr_copy(char *s, char c, int *i);
int					ft_strncmp_copy(const char *s1, const char *s2, size_t n,
						int *j);
char				**ft_split_spaces(t_data_shell *mshell, char *s);

int					len(const char *s, int i);
char				**ft_free_all(char **strs, int j);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

///////////////////////////////////////////////////////////////////

size_t				ft_strlen(const char *s);
void				*gc_malloc(size_t allocate, t_gc **list);
void				add_to_list(t_gc **list, t_gc *node);
t_gc				*ft_gc_new(void *ptr);
void				free_gc(t_gc **list);
void				token_line(t_data_shell *mshell, t_cmd *file);
int					check_syntax(t_data_shell *mshell, t_cmd *line,
						t_cline **list, char **env);
void				making_list(t_cmd *file, t_cline **list);
void				check_to_split(t_data_shell *mshell, t_cline *tmp,
						t_exp_info *vr, int *j);

char				*dq_fct(t_data_shell *mshell, char *str, int *j);
char				*out_quotes(t_data_shell *mshell, t_cline *tmp, int *j,
						t_exp_info *vr);
void				update_optns(t_data_shell *mshell, t_cline *tmp,
						t_exp_info *vr, int *change_i2);
char				*no_expand(t_data_shell *mshell, char *str, int *j);
char				*ability_to_expand(t_data_shell *mshell, char *str);
char				*ft_substr(t_data_shell *mshell, char const *s,
						unsigned int start, size_t len);
int					countsep(char const *s);
void				red_expand(t_data_shell *mshell);
///
char				*ft_strjoin(t_data_shell *mshell, char const *s1,
						char const *s2);
void				delete_quotes(t_data_shell *mshell);
void				error_function(t_data_shell *mshell);

// char				**ft_split_2(t_data_shell *mshell, char const *s, char c);
///

void				expand(t_data_shell *mshell);
char				*check_expnd(t_data_shell *mshell, t_cline *tmp);
void				apply_signals(t_data_shell *mshell);

#endif