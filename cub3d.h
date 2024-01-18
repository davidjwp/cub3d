/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/18 19:29:48 by djacobs          ###   ########.fr       */
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

typedef struct s_star{
	int		distance;
	t_pos	start;
	t_pos	end;
}t_star;

//node position, wall = 1 not wall = 0, space, visited
typedef struct s_nodes{
	t_pos	p;
	bool	w;
	bool	s;
	bool	visited;
}t_nodes;

typedef struct s_mdata{
	char	**map;
	char	**tex;
	t_nodes	**m_nodes;
	int		tc_index[6];
	t_pos	mlw;
}t_mdata;

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

/*		UtilsC			*/
int		find_highest(int *index);
bool	l_issp(char	*map);
void	free_nodes(t_nodes **nodes, t_pos mlw, int index);
t_pos	get_mlw(char **map);
void	set_node(t_nodes *n, bool s, bool w, t_pos p);

/*		u_test			*/
void	print_map(char **map);
void	PrintNodes(t_mdata *f);

#endif