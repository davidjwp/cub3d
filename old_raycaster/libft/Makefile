# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 12:34:33 by djacobs           #+#    #+#              #
#    Updated: 2024/01/15 17:22:04 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
SRCS		= ft_atoi.c ft_isdigit.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c \
			ft_strrchr.c ft_bzero.c ft_isprint.c ft_memmove.c ft_split.c \
			ft_strlcpy.c ft_strtrim.c  ft_calloc.c ft_itoa.c ft_memset.c \
			ft_strchr.c ft_strlen.c ft_substr.c ft_isalnum.c ft_putchar_fd.c \
			ft_strdup.c ft_strmapi.c ft_tolower.c ft_isalpha.c ft_memchr.c \
			ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c  ft_isascii.c \
			ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c

OBJS		= $(SRCS:.c=.o)

BONUS_SRCS	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)
CC		= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $(OBJS) && ranlib $@

bonus: $(BONUS_OBJS)
	ar rc $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
