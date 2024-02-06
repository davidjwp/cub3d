# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 14:07:50 by djacobs           #+#    #+#              #
#    Updated: 2024/02/06 21:52:13 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#add rule for compiling on dells vs macs that change the speed of the character
#and the speed of looking left and right
NAME		:= cub3D
CC			:= gcc
CFLAGS		:= -g3 -Wall -Werror -Wextra

INC_DIR		:= -Iinclude -I ./minilibx-linux
MLX			:= -L./minilibx-linux
MIN_LIBX	= ./minilibx-linux/libmlx_Linux.a ./minilibx-linux/libmlx.a

HEADER		:= include/cub3d.h

LINKER		:= -Llibft -lmlx -lXext -lX11 -lm -ldl -lglfw
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:=	srcs/main.c \
				srcs/Parsing/parser.c \
				srcs/Parsing/Parser_utilsA.c \
				srcs/Parsing/Parser_utilsB.c \
				srcs/Parsing/Parser_utilsC.c \
				srcs/Parsing/cr_map.c \
				srcs/Parsing/cr_nodes.c \
				srcs/Parsing/texcol_check.c \
				srcs/Renderer/controls/hook_functions.c \
				srcs/Renderer/controls/exit_game.c \
				srcs/Renderer/controls/move_player.c \
				srcs/Renderer/controls/rotate_player.c \
				srcs/Renderer/get_texcol.c \
				srcs/Renderer/Renderer_utilsA.c \
				srcs/Renderer/minimap.c \
				srcs/Renderer/raycast.c \
				srcs/Prints.c \
				new_renderer.c

OBJ_DIR		:= obj/
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)%.o)


all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT) $(MIN_LIBX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LINKER)  -o $(NAME)

$(OBJ_DIR)%.o: %.c $(HEADER)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MIN_LIBX):
	make -C ./minilibx-linux/

clean:
	rm -fr $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
