# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 14:07:50 by djacobs           #+#    #+#              #
#    Updated: 2024/01/16 14:17:20 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

CC			= cc

CFLAGS		= -Wall -Werror -Wextra

HEADER		= cub3d.h

LIB			= libft/libft.a

SRCS		=	Parser.c \
				utilsA.c \
				utilsB.c \

OBJS_DIR	= objs/
OBJS		= $(SRCS:srcs/%.c=$(OBJS_DIR)%.o)

all:$(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(OBJS_DIR)%.o: srcs/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LIB):
	@make -s -C libft/

clean:
	@rm -f $(OBJS)
	@make clean -C libft/
	
fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C libft/ 

re: fclean all

.PHONY: fclean clean all
