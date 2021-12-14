# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokino <tokino@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 14:31:56 by tokino            #+#    #+#              #
#    Updated: 2021/12/09 21:25:52 by tokino           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c		ft_bzero.c		ft_calloc.c		\
		ft_isalnum.c	ft_isalpha.c	ft_isascii.c	\
		ft_isdigit.c	ft_isprint.c	ft_itoa.c		\
		ft_memccpy.c	ft_memchr.c		ft_memcmp.c		\
		ft_memcpy.c		ft_memmove.c	ft_memset.c		\
		ft_putchar_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	\
		ft_putstr_fd.c	ft_split.c		ft_strchr.c		\
		ft_strdup.c		ft_strjoin.c	ft_strlcat.c	\
		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	\
		ft_strncmp.c	ft_strnstr.c	ft_strrchr.c	\
		ft_strtrim.c	ft_substr.c		ft_tolower.c	\
		ft_toupper.c	get_min.c		get_max.c		\
		ft_strndup.c	ft_str2joins.c

SRC_BONUS = ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c	\
			ft_lstdelone.c		ft_lstiter.c		ft_lstlast.c	\
			ft_lstmap.c			ft_lstnew.c			ft_lstsize.c

HEADER = libft.h
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar -rcs
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(LIBC)  $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS) $(HEADER)
	$(LIBC) $(NAME) $(OBJ) $(OBJ_BONUS)
	
clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
