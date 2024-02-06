/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/06 21:54:03 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <unistd.h>

# include "../libft/libft.h"
# include <mlx.h>

# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF
# define GREEN 0x0000FF00
# define DGREEN 0x0000B500
# define BLUE 0x000000FF
# define BUF_SIZ 8192
# define WIDTH 1280
# define HEIGHT 720

# define SCALE 0.1
# define RAYS 16
# define MINRAY GREEN
# define MAPS 256
# define BUF_SIZ 8192
# define RS 0.02
# define MS 0.04

typedef struct s_pos{
	int	x;
	int	y;
}t_pos;

typedef struct s_p{
	double	x;
	double	y;
}t_p;

typedef struct s_star{
	int		distance;
	t_pos	start;
	t_pos	end;
}t_star;

typedef struct s_minimap{
	t_pos	offs;
	t_pos	world;
	t_pos	scale;
}t_minmap;

typedef struct s_line{
	t_pos	delta;
	t_pos	sign;
	t_pos	err;
	t_pos	world;
	t_pos	or;
	t_pos	limity;
	t_pos	limitx;
	t_pos	map;
}t_minline;

typedef struct s_nodes{
	t_pos	p;
	bool	w;
	bool	s;
	bool	c;
	bool	visited;
}t_n;

typedef struct s_xpms{
	void	*img;
	char	*add;
	int		bpp;
	int		len;
	int		end;
	int		imgw;
	int		imgh;
}t_xpms;

typedef struct s_mdata{
	char	**map;
	char	*tex[7];
	t_n		**m_nodes;
	int		tc_index[6];
	t_pos	cpos;
	t_pos	mlw;
	int		col[2];
	char	pl_sp_dir;
}t_mdata;

typedef struct s_lst{
	t_n				*node;
	struct s_lst	*next;
}t_lst;

enum	e_tex{
	NO,
	SO,
	WE,
	EA,
	F,
	C,		
};

typedef struct s_key{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	p;
	bool	mouse;
	bool	la;
	bool	ra;
}t_key;

typedef struct s_img{
	void	*img[2];
	char	*add[2];
	int		bpp;
	int		len;
	int		end;
	int		current;
}t_img;

typedef struct s_ray{
	t_p		pos;
	t_p		dir;
	t_p		plane;
	t_p		camera;
	t_p		raydir;
	t_p		sdist;
	t_p		ddist;
	t_pos	step;
	t_pos	map;
	bool	side;
	bool	hit;
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	movespeed;
	double	rotspeed;
}t_ray;

typedef struct s_mlx{
	void	*mlx;
	void	*win;
	char	**map;
	t_pos	mxy;
	t_img	*i3d;
	t_img	*i;
	t_key	*k;
	int		col[2];
	t_ray	r;
	t_xpms	xpms[4];
	char	pl_sp_dir;
}t_mlx;

/*=======================Parser=======================*/

/*		parser			*/
bool	file_parse(t_mdata *fdata);

/*		UtilsA			*/
bool	ismap(char c);
bool	ischar(char c);
bool	l_ismap(char *l);
bool	err_msg(const char *msg);
void	clean(t_mdata mdata);

/*		UtilsB			*/
int		gnl(int fd, char **str, int i, int n);
int		find_map(t_mdata *fdata, t_pos *p);
bool	is_full(char **map);
int		find_highest(int *index);

/*		UtilsC			*/
bool	l_issp(char	*map);
bool	free_lst(t_lst *l);
bool	find_nchar(t_n **start, t_mdata *f, t_pos *p);
bool	n_open(t_n **node, t_pos p, t_pos mlw);

/*		cr_map			*/
bool	cr_map(t_mdata *fdata);
bool	texcol_check(t_mdata *fd, int i, int y);

/*		cr_nodes		*/
bool	cr_nodes(t_mdata *fdata);
void	free_nodes(t_n **nodes, t_pos mlw, int index);

/*		Prints			*/
void	print_map(char **map);
void	tty_print(t_mdata *f, t_lst *l, t_n *c, int i);

/*=======================Renderer=======================*/

/*		Renderer		*/
int		start_renderer(t_mdata *fdata);

/*		get_texcol		*/
bool	xpm_check(t_mdata *d, t_mlx *m, void *mlx);
bool	col_check(t_mdata *d);

/*		Minimap			*/
void	minimap(t_mlx *d, t_ray *r);

/*		UtilsA			*/
bool	outmap(t_pos start, t_minline mini);
void	swap_buffers(t_mlx *data);
void	pixput(t_img *i, int x, int y, int color);
void	drawstrip(t_img *i, int x, int *y, int color);

/*		raycast			*/
void	raycast(t_mlx *d, t_ray *r);

void	drawplayer(t_mlx *d, int x, int y);
void	caldrawstrip(t_mlx *d, t_ray *r, int x);

/*=======================Controls*/

/*	check_collisions	*/
int		check_collision_ws(char key, t_mlx *d);
int		check_collision_da(char key, t_mlx *d);

/*		hook_functions	*/
int		mouse(int mouseX, int mouseY, t_mlx *d);
int		key_press(int key, void *param);
int		key_release(int key, void *param);

/*		exit_game		*/
int		close_win(int key, void *param);

/*		move_player		*/
void	upkey(t_mlx *d, t_ray *r);
void	downkey(t_mlx *d, t_ray *r);
void	rightkey(t_mlx *d, t_ray *r);
void	leftkey(t_mlx *d, t_ray *r);

/*		rotate_player	*/
void	rotate_right(t_ray *r);
void	rotate_left(t_ray *r);


#endif
