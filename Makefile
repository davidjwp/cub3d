# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 14:07:50 by djacobs           #+#    #+#              #
#    Updated: 2024/01/20 20:37:34 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= test
CC			:= gcc
CFLAGS		:= -g3 -Wall -Werror -Wextra

INC_DIR		:= -Iinclude -IMLX42/include
MLX			:= MLX42/build/libmlx42.a

HEADER		:= cub3d.h

LINKER		:= -Llibft -LMLX42/build -lmlx42 -lXext -lX11 -lm -ldl -lglfw
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:=	Parser.c \
				utilsA.c \
				utilsB.c \
				utilsC.c \
				u_test.c \
				cr_map.c \
				cr_nodes.c \

OBJS		:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LINKER)  -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
