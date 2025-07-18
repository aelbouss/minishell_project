NAME = minishell

SRC = main.c parsing/garbage_collector.c parsing/making_list/token.c parsing/making_list/check_syntaxe.c \
	parsing/making_list/making_list.c expand/expand.c expand/expand_inside_dq.c expand/expand_outside_dq.c\
	expand/expand_redr.c parsing/making_list/delete_quotes.c parsing/signals.c herdoc_expand/expand_hed.c  \
	builtins/builtins_utils.c execution/_split.c execution/execution_utils2.c envs/env_utils.c envs/env_utils2.c\
	builtins/ft_cd.c builtins/ft_echo.c builtins/ft_pwd.c builtins/ft_env.c builtins/ft_export.c envs/env_utils3.c\
	envs/fg_split.c builtins/ft_unset.c execution/heredoc.c execution/operators.c  execution/execution_utils.c \
	execution/execution.c builtins/ft_exit.c execution/execution_utils3.c execution/execution_utils4.c \
	execution/execution_utils5.c herdoc_expand/fcts_her.c execution/execution_utils6.c execution/execution_utils7.c\
	execution/execution_utils8.c execution/execution_utils9.c builtins/builtins_utils2.c builtins/builtins_utils3.c\
	execution/execution_utils10.c

OBJ =$(SRC:.c=.o)
LIBFT_DIR =libft
LIBFT =$(LIBFT_DIR)/libft.a
CC = cc 

CFLAGS = -Wall -Wextra -Werror #-g -g3 -fsanitize=address 


all : $(LIBFT) $(NAME)

$(NAME) :$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  $(LIBFT) -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	
fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.SECONDARY : $(OBJ)
