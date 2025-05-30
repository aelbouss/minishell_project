NAME = minishell

SRC = main.c garbage_collector.c making_list/token.c making_list/check_syntaxe.c \
	making_list/making_list.c expand/expand.c expand/expand_inside_dq.c expand/expand_outside_dq.c\
	 expand/expand_redr.c making_list/delete_quotes.c signals.c
OBJ =$(SRC:.c=.o)
LIBFT_DIR =libft
LIBFT =$(LIBFT_DIR)/libft.a
CC = cc 

CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g3


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