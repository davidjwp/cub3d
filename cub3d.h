/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/16 16:44:29 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft/libft.h"

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

/*		UtilsA			*/
bool	ismap(char c);
bool	ischar(char c);
bool	l_ismap(char *l);
bool	err_msg(const char *msg);
void	clean_all(char *buf, t_mdata mdata, int fd);

/*		UtilsB			*/
int		gnl(int fd, char **str, int i, int n);
bool	is_texcol(int pos, t_mdata *fdata);
int		find_map(t_mdata *fdata, t_pos *p);
bool	is_full(char **map);

#endif