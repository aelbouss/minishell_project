/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:03:34 by memahamo          #+#    #+#             */
/*   Updated: 2025/06/21 16:27:32 by aelbouss         ###   ########.fr       */
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
# include <sys/wait.h>
# include <limits.h>
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

typedef	struct	s_fg
{
	void			*add;
	struct s_fg		*next;
}					t_fg;


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
	char			f_path[10];
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
	int				flag;
	struct s_env	*next;
}					t_env;

typedef	struct	s_exec
{
	char	*path;
	char	**sp;
	char	**gep;
}	t_exec;

typedef struct s_data_shell
{
	t_cmd			line;
	t_cline			*list;
	t_env			*env_list;
	t_exec			*exec;
	int				exit_status;
	int				nc;
	t_fg			*fgc;
	int				r_sign;
	
}					t_data_shell;


typedef struct s_exp_info
{
	char			**expand_result;
	int				j;
	int				count_word;
	char			*mdf_option;
	char			*return_fnct;
	char			q_char;
	int				len;
	int				j2;
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
char				*join_q(t_data_shell *mshell, char const *s1, char s2);

///////////////////////////////////////////////////////////////////

size_t				ft_strlen(const char *s);
void				*gc_malloc(size_t allocate, t_gc **list);
void				add_to_list(t_gc **list, t_gc *node);
t_gc				*ft_gc_new(void *ptr);
void				free_gc(t_gc **list);
void				token_line(t_data_shell *mshell, t_cmd *file);
int					check_syntax(t_data_shell *mshell, t_cmd *line, t_cline **list);
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
int					error_function(t_data_shell *mshell);

void				expand(t_data_shell *mshell);
char				*check_expnd(t_data_shell *mshell, t_cline *tmp);
void				apply_signals(t_data_shell *mshell);
char				*her_fcts(t_data_shell *mshell, char *line);
char				*out_quotes_her(t_data_shell *mshell, char *line, int *j);
char				*no_expand_her(t_data_shell *mshell, char *str, int *j,
						char c);
char				*expand_inside_dq_her(t_data_shell *mshell, char *str,
						t_exp_info *her);

//////////////////////////////// envs /////////////////////////

char	*extract_name(t_data_shell *p, char *str);
char	*extract_value(t_data_shell *p, char *str);
int	split_each_env(t_data_shell *p,	char *str, char **name, char **value);
t_env	*build_node(t_data_shell *p,  char *str);
int	build_env_list(t_data_shell *p, char *str);
void	add_to_linkedlist(t_env **lst, t_env *new);
void	create_env_list(t_data_shell *p, char **envp);
char	**turn_list_to_arr(t_env *lst, t_data_shell *p);
int		list_len(t_cline *lst);
char	*concat_and_free(t_data_shell *p, char *s1, char *s2);


///////////////////////////////// builtins ///////////////////////////////////

int		check_is_builtin(t_cline *node, t_data_shell *p, t_env *lst);
int		ft_cd(t_data_shell *p, t_env *env_lst ,char *path);
int		ft_echo(char **args);
int		ft_pwd(t_data_shell *p);
int		ft_env(t_data_shell *p);
int		ft_exit(t_cline *node, t_data_shell *p);
int		ft_unset(t_data_shell *p, t_env **lst);
char	*get_env_value(t_data_shell *p, t_env *eh, char *env_name);
int		check_to_modify(t_data_shell *p, char *name, char *new_value);
int		ft_export(t_data_shell *p, t_cline *node);
int		search_for_char(char *s, int n);
int		print_envs(t_env *lst);
int		is_valid_identifier(int c);

//////////////////////////// execution /////////////////////////

char	*extract_path_env(char **envp);
char	**get_splited_path(char *path, t_data_shell *p);
char	*build_absolute_path(char *path, char *cmd, t_data_shell *p);
char	*check_if_exe(char **envp, char *cmd, t_data_shell *p);
int		execute_exe(char **cmd, char **envp , t_data_shell *p);
int		loop_and_execute(t_cline *lst, char **envp, t_data_shell *p);
char	**s_split(t_data_shell *p ,char const *s, char c);
int		handle_operators(t_data_shell *p  ,t_redr *operator, char	**commands);
int		**open_pipes(t_data_shell *p);
void	close_pipes(int **pipes);
int		handle_pipes(int np, int **pipes, int idx);
int		heardoc(t_data_shell *mshell,  char *keyword, int fd);
void	heardoc_heandler(t_data_shell *p, t_cline *lst);
void	__setup_utils__(t_data_shell *mshell, char **envp, t_exec *container);

/////////////////////////// final garbage ///////////////////////////////

t_fg	*fg_new(void *ptr);
void	*fg_malloc(size_t allocate, t_fg **list);
void	fg_add_to_list(t_fg **list, t_fg *node);
void	fg_free_gc(t_fg **list);
char	*fg_stdup(t_data_shell *p ,const char *src, int len);
char	**fg_split(t_data_shell *p ,char const *s, char c);
char	*s_strdup(t_data_shell *p, char *src);
char	*s_substr(t_data_shell *p, const char *s, unsigned int start, size_t len);
int	build_env_list(t_data_shell *p, char *str);
void	clear_ressources(t_data_shell *p);

#endif