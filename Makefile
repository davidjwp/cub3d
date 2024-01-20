# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 14:07:50 by djacobs           #+#    #+#              #
#    Updated: 2024/01/20 23:00:56 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= test
CC			:= gcc
CFLAGS		:= -g3 -Wall -Werror -Wextra

INC_DIR		:= -Iinclude -IMLX42/include
MLX			:= MLX42/build/libmlx42.a

HEADER		:= include/cub3d.h

LINKER		:= -Llibft -LMLX42/build -lmlx42 -lXext -lX11 -lm -ldl -lglfw
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:=	srcs/main.c \
				srcs/Parsing/parser.c \
				srcs/Parsing/utilsA.c \
				srcs/Parsing/utilsB.c \
				srcs/Parsing/utilsC.c \
				u_test.c \
				srcs/Parsing/cr_map.c \
				srcs/Parsing/cr_nodes.c \

OBJ_DIR		:= obj/
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LINKER)  -o $(NAME)

$(OBJ_DIR)%.o: %.c $(HEADER)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -fr $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
