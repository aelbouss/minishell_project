# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memahamo <memahamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 17:04:05 by memahamo          #+#    #+#              #
#    Updated: 2025/07/13 02:32:59 by memahamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC= ft_isalpha.c\
     ft_isdigit.c\
     ft_isalnum.c\
     ft_isascii.c\
     ft_isprint.c\
     ft_toupper.c\
     ft_tolower.c\
     ft_strchr.c\
     ft_strrchr.c\
     ft_strncmp.c\
     ft_memchr.c\
     ft_strnstr.c\
     ft_atoi.c\
     ft_strlen.c\
     ft_memset.c\
     ft_bzero.c\
     ft_memmove.c\
     ft_strlcpy.c\
     ft_strlcat.c\
     ft_calloc.c\
     ft_strdup.c\
     ft_memcmp.c\
     ft_substr.c\
     ft_strjoin.c\
     ft_strtrim.c\
     ft_split.c\
     ft_itoa.c\
     ft_strmapi.c\
     ft_striteri.c\
     ft_putchar_fd.c\
     ft_putstr_fd.c\
     ft_putendl_fd.c\
     ft_putnbr_fd.c\
     ft_memcpy.c\
     ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
     ft_lstclear_bonus.c\
     ft_lstiter_bonus.c\
	ft_lstmap_bonus.c\
     ft_strcmp.c\
     ft_strchr_copy.c\
     ft_strncmp_copy.c\
     split_spaces.c\
     ft_strjoin_copy.c
 
OBJ= $(SRC:.c=.o)
CC= cc
CFLAGS= -Wall -Wextra  -Werror #-fsanitize=address -g3
RM= rm -f
AR= ar -rc
                                                                           
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)	

all: $(NAME)

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SECONDARY : $(OBJ)

