/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/15 21:54:18 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft/libft.h"

# define BUF_SIZ 8192

typedef struct s_pos{
	int	x;
	int	y;
}t_pos;

typedef struct s_mdata{
	char	**map;
	char	**tex;
	int		tc_index[6];
}t_mdata;

typedef struct star_s {
	t_pos	start;
	t_pos	end;
	t_pos	mapwl;
	int		distance;
	int		exit;
	int		items;
	int		dt_items;
}t_star;

enum e_textures{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
};

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
bool	err_msg(const char *msg);
int		gnl(int fd, char **str, int i, int n);
bool	l_ismap(char *l);
bool	ismap(char c);
bool	ischar(char c);
void	clean_all(char *buf, t_mdata mdata, int fd);

#endif