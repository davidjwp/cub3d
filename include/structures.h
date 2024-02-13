/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:31:53 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/12 11:38:20 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
# define MS 0.02

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_p
{
	double	x;
	double	y;
}	t_p;

typedef struct s_star
{
	int		distance;
	t_pos	start;
	t_pos	end;
}	t_star;

typedef struct s_minimap
{
	t_pos	offs;
	t_pos	world;
	t_pos	scale;
}	t_minmap;

typedef struct s_line
{
	t_pos	delta;
	t_pos	sign;
	t_pos	err;
	t_pos	world;
	t_pos	or;
	t_pos	limity;
	t_pos	limitx;
	t_pos	map;
}	t_minline;

typedef struct s_conf
{
	t_list	*source;
	char	*no[PATH_MAX + 1];
	char	*so[PATH_MAX + 1];
	char	*we[PATH_MAX + 1];
	char	*ea[PATH_MAX + 1];
	uint8_t	c[3];
	uint8_t	f[3];
	int		c_color;
	int		f_color;
}		t_conf;

typedef struct s_nodes
{
	t_pos	p;
	bool	w;
	bool	s;
	bool	c;
	bool	visited;
}	t_n;

typedef struct s_xpms
{
	void	*img;
	char	*add;
	int		bpp;
	int		len;
	int		end;
	int		imgw;
	int		imgh;
}	t_xpms;

typedef struct s_mdata
{
	char	**map;
	char	*tex[7];
	t_n		**m_nodes;
	int		tc_index[6];
	t_pos	cpos;
	t_pos	mlw;
	int		col[2];
	char	pl_sp_dir;
}	t_mdata;

typedef struct s_lst
{
	t_n				*node;
	struct s_lst	*next;
}	t_lst;

enum	e_tex
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,		
};

typedef struct s_key
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	p;
	bool	mouse;
	bool	la;
	bool	ra;
}	t_key;

typedef struct s_img
{
	void	*img[2];
	char	*add[2];
	int		bpp;
	int		len;
	int		end;
	int		current;
}	t_img;

typedef struct s_ray
{
	t_p		pos;
	t_p		dir;
	t_p		plane;
	t_p		camera;
	t_p		raydir;
	t_p		sdist;
	t_p		ddist;
	t_pos	step;
	t_pos	map;
	t_pos	tex;
	bool	side;
	bool	hit;
	double	perpwalldist;
	double	wallx;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	movespeed;
	double	rotspeed;
	double	drawstep;
	double	texpos;
	t_xpms	current_xpm;
}	t_ray;

typedef struct s_mlx
{
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
	t_conf	conf;
}	t_mlx;

#endif
