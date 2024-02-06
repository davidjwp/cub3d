/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:55:48 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/06 22:23:33 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_minline	*lineinit(t_minline *mi, t_pos s, t_pos e, t_minmap m)
{
	mi->delta = (t_pos){(abs(e.x - s.x)), (-abs(e.y - s.y))};
	mi->err = (t_pos){(mi->delta.x + mi->delta.y), 0};
	mi->sign = (t_pos){-1, -1};
	mi->or = (t_pos){s.x, s.y};
	if (s.x < e.x)
		mi->sign.x = 1;
	if (s.y < e.y)
		mi->sign.y = 1;
	mi->limitx.x = (MAPS / 2 + m.offs.x) - (MAPS / 2);
	mi->limitx.y = mi->limitx.x + MAPS;
	mi->limity.x = (MAPS / 2 + m.offs.y) - (MAPS / 2);
	mi->limity.y = mi->limity.x + MAPS;
	return (mi);
}

static void	miniline(t_mlx *d, t_pos start, t_ray *r, t_minline *m)
{
	while (1)
	{
		m->map = (t_pos){(r->pos.x + (start.x - m->or.x) * SCALE), \
			(r->pos.y + (start.y - m->or.y) * SCALE)};
		if (m->map.y < d->mxy.y && m->map.x < (int)ft_strlen(d->map[m->map.y]))
			m->world = (t_pos){m->map.x, m->map.y};
		pixput(d->i, start.x, start.y, MINRAY);
		if (outmap(start, *m) || d->map[m->world.y][m->world.x] == '1')
			break ;
		m->err.y = 2 * m->err.x;
		if (m->err.y >= m->delta.y)
		{
			m->err.x += m->delta.y;
			start.x += m->sign.x;
		}
		if (m->err.y <= m->delta.x)
		{
			m->err.x += m->delta.x;
			start.y += m->sign.y;
		}
	}
}

static void	minicast(t_mlx *d, t_ray *r, t_minmap min)
{
	t_pos	end;
	t_pos	start;
	t_p		raydir;
	double	rp;
	int		i;

	i = -1;
	start = (t_pos){(MAPS / 2 + min.offs.x), (MAPS / 2 + min.offs.y)};
	while (++i < RAYS)
	{
		rp = (2 * ((double)i / (RAYS - 1)) - 1);
		raydir.x = r->dir.x + r->plane.x * rp;
		raydir.y = r->dir.y + r->plane.y * rp;
		end.x = start.x + (int)((MAPS / 2) * raydir.x);
		end.y = start.y + (int)((MAPS / 2) * raydir.y);
		miniline(d, start, r, lineinit(&(t_minline){{0, 0}, {0, 0}, {0, 0}, \
		{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, start, end, min));
	}
}

static void	drawmap(t_mlx *d, t_pos m, t_minmap min)
{
	int	color;

	color = 0;
	if (d->map[min.world.y][min.world.x] == '1')
		color = 0xFFFFFF;
	else if (d->map[min.world.y][min.world.x] == '0')
		color = 0x000000;
	else if (!ismap(d->map[min.world.y][min.world.x]))
		color = -1;
	pixput(d->i, m.x + min.offs.x, m.y + min.offs.y, color);
}

void	minimap(t_mlx *d, t_ray *r)
{
	t_pos		m;
	t_minmap	min;

	m = (t_pos){-1, -1};
	min = (t_minmap){{(WIDTH - MAPS - 16), (HEIGHT - MAPS - 16)}, {0, 0}, \
	{(d->mxy.x / MAPS), (d->mxy.y / MAPS)}};
	while (++m.y < MAPS)
	{
		while (++m.x < MAPS)
		{
			min.world.x = (int)(r->pos.x + (m.x - MAPS / 2) * SCALE);
			min.world.y = (int)(r->pos.y + (m.y - MAPS / 2) * SCALE);
			if (min.world.y >= 0 && min.world.y < d->mxy.y && \
				min.world.x >= 0 && min.world.x < \
				(int)ft_strlen(d->map[min.world.y]))
				drawmap(d, m, min);
		}
		m.x = -1;
	}
	drawplayer(d, (MAPS / 2 + min.offs.x) - 4, (MAPS / 2 + min.offs.y) - 4);
	minicast(d, r, min);
}
