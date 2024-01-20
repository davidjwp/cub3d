/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/20 21:43:44 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define BUF_SIZ 8192
# define WIDTH 512
# define HEIGHT 512
# define BLOCK 32;

typedef struct s_pos{
	int	x;
	int	y;
}t_pos;

typedef struct s_star{
	int		distance;
	t_pos	start;
	t_pos	end;
}t_star;

//node position, wall = 1 not wall = 0, space, character, visited
typedef struct s_nodes{
	t_pos	p;
	bool	w;
	bool	s;
	bool	c;
	bool	visited;
}t_n;

typedef struct s_mdata{
	char	**map;
	char	**tex;
	t_n		**m_nodes;
	int		tc_index[6];
	t_pos	mlw;
}t_mdata;

typedef struct s_cub3D{
	t_mdata	fdata;
	mlx_t	*mlx;
}t_cub;

typedef struct s_lst{
	t_n			*node;
	struct s_lst	*next;
}t_lst;

/*					Parser					*/
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
bool	free_lst(t_lst *l);

/*		cr_map			*/
bool	cr_map(t_mdata *fdata);
bool	texcol_check(t_mdata *fd, int i, int y);

/*		cr_nodes		*/
bool	cr_nodes(t_mdata *fdata);
void	free_nodes(t_n **nodes, t_pos mlw, int index);

/*		u_test			*/
void	print_map(char **map);
void	PrintNodes(t_mdata *f);
void	tty_print(t_mdata *f, t_lst *l, t_n *c, int i);


#endif