NAME = minishell

SRC = main.c   env/list_of_envs.c  parsing/garbage_collector.c execution/execution_utils.c \
execution/loop_trough_args_and_exec.c parsing/token.c parsing/making_list.c parsing/check_syntaxe.c builtins/ft_cd.c\
builtins/ft_echo.c builtins/ft_pwd.c builtins/ft_export.c builtins/ft_env.c builtins/ft_unset.c\
builtins/ft_exit.c execution/_split.c execution/operators.c execution/heardoc.c execution/pipes.c

OBJ =$(SRC:.c=.o)
LIBFT_DIR =libft
LIBFT =$(LIBFT_DIR)/libft.a
CC = cc 

CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g3


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
