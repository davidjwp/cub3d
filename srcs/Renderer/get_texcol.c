/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texcol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:40:13 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/06 20:49:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	xpm_getaddr(t_mlx *m)
{
	mlx_get_data_addr(m->xpms[NO].img, \
	&m->xpms[NO].bpp, &m->xpms[NO].len, &m->xpms[NO].end);
	mlx_get_data_addr(m->xpms[SO].img, \
	&m->xpms[SO].bpp, &m->xpms[SO].len, &m->xpms[SO].end);
	mlx_get_data_addr(m->xpms[WE].img, \
	&m->xpms[WE].bpp, &m->xpms[WE].len, &m->xpms[WE].end);
	mlx_get_data_addr(m->xpms[EA].img, \
	&m->xpms[EA].bpp, &m->xpms[EA].len, &m->xpms[EA].end);
}

bool	xpm_check(t_mdata *d, t_mlx *m, void *mlx)
{
	m->xpms[NO].img = mlx_xpm_file_to_image(mlx, d->tex[NO], \
	&m->xpms[NO].imgw, &m->xpms[NO].imgh);
	if (m->xpms[NO].img == NULL)
		return (false);
	m->xpms[SO].img = mlx_xpm_file_to_image(mlx, d->tex[SO], \
	&m->xpms[SO].imgw, &m->xpms[SO].imgh);
	if (m->xpms[SO].img == NULL)
		return (mlx_destroy_image(mlx, m->xpms[NO].img), false);
	m->xpms[WE].img = mlx_xpm_file_to_image(mlx, d->tex[WE], \
	&m->xpms[WE].imgw, &m->xpms[WE].imgh);
	if (m->xpms[WE].img == NULL)
		return (mlx_destroy_image(mlx, m->xpms[NO].img), \
		mlx_destroy_image(mlx, m->xpms[SO].img), false);
	m->xpms[EA].img = mlx_xpm_file_to_image(mlx, d->tex[EA], \
	&m->xpms[EA].imgw, &m->xpms[EA].imgh);
	if (m->xpms[EA].img == NULL)
		return (mlx_destroy_image(mlx, m->xpms[NO].img), \
		mlx_destroy_image(mlx, m->xpms[SO].img), \
		mlx_destroy_image(mlx, m->xpms[EA].img), false);
	xpm_getaddr(m);
	return (true);
}

static bool	rgb(char **s, unsigned int *r, unsigned int *g, unsigned int *b)
{
	if (s == NULL)
		return (err_msg("rgb_to_hex split fail"));
	if (s[0] == NULL || s[1] == NULL || s[2] == NULL || \
		*s[0] == ',' || *s[1] == ',' || *s[2] == ',')
		return (free_split(s, 0), err_msg("Colors missing or empty values"));
	*r = ft_atoi(s[0]);
	*g = ft_atoi(s[1]);
	*b = ft_atoi(s[2]);
	return (free_split(s, 0), true);
}

static bool	rgb_to_hex(t_mdata *d)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!rgb(ft_split(d->tex[F], ','), &r, &g, &b))
		return (false);
	if (b > 255 || g > 255 || r > 255)
		return (err_msg("Floor values too high"));
	d->col[0] = (r << 16) | (g << 8) | b;
	if (!rgb(ft_split(d->tex[C], ','), &r, &g, &b))
		return (false);
	if (b > 255 || g > 255 || r > 255)
		return (err_msg("Floor values too high"));
	d->col[1] = (r << 16) | (g << 8) | b;
	return (true);
}

bool	col_check(t_mdata *d)
{
	t_pos	p;

	p = (t_pos){-1, -1};
	while (++p.y < 2)
	{
		while (d->tex[F + p.y][++p.x])
			if (d->tex[F + p.y][p.x] != 44 && d->tex[F + p.y][p.x] != 32 && \
			d->tex[F + p.y][p.x] != 9 && !ft_isdigit(d->tex[F + p.y][p.x]))
				return (err_msg("Bad col input"), false);
		p.x = -1;
	}
	if (!rgb_to_hex(d))
		return (false);
	return (true);
}
