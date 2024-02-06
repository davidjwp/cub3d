/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:36:37 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/06 22:28:52 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	upkey(t_mlx *d, t_ray *r)
{
	if (d->map[(int)(r->pos.y + r->dir.y * MS)][(int)r->pos.x] != '1')
		r->pos.y += r->dir.y * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x + r->dir.x * MS)] != '1')
		r->pos.x += r->dir.x * MS;
}

void	downkey(t_mlx *d, t_ray *r)
{
	if (d->map[(int)(r->pos.y - r->dir.y * MS)][(int)r->pos.x] != '1')
		r->pos.y -= r->dir.y * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x - r->dir.x * MS)] != '1')
		r->pos.x -= r->dir.x * MS;
}

void	rightkey(t_mlx *d, t_ray *r)
{
	double	pl_dir;

	pl_dir = atan2(r->dir.y, r->dir.x);
	if (d->map[(int)(r->pos.y + \
	sin(pl_dir + M_PI_2) * MS)][(int)r->pos.x] != '1')
		r->pos.y += sin(pl_dir + M_PI_2) * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x + \
	cos(pl_dir + M_PI_2) * MS)] != '1')
		r->pos.x += cos(pl_dir + M_PI_2) * MS;
}

void	leftkey(t_mlx *d, t_ray *r)
{
	double	pl_dir;

	pl_dir = atan2(r->dir.y, r->dir.x);
	if (d->map[(int)(r->pos.y + \
	sin(pl_dir - M_PI_2) * MS)][(int)r->pos.x] != '1')
		r->pos.y += sin(pl_dir - M_PI_2) * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x + \
	cos(pl_dir - M_PI_2) * MS)] != '1')
		r->pos.x += cos(pl_dir - M_PI_2) * MS;
}
