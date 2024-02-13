/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:36:37 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/12 11:25:11 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	upkey(t_mlx *d, t_ray *r)
{
	if (d->map[(int)(r->pos.y + r->dir.y * MS)][(int)r->pos.x] != '1')
		r->pos.y += r->dir.y * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x + r->dir.x * MS)] != '1')
		r->pos.x += r->dir.x * MS;
}

static void	downkey(t_mlx *d, t_ray *r)
{
	if (d->map[(int)(r->pos.y - r->dir.y * MS)][(int)r->pos.x] != '1')
		r->pos.y -= r->dir.y * MS;
	if (d->map[(int)r->pos.y][(int)(r->pos.x - r->dir.x * MS)] != '1')
		r->pos.x -= r->dir.x * MS;
}

static void	rightkey(t_mlx *d, t_ray *r)
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

static void	leftkey(t_mlx *d, t_ray *r)
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

int	buttons(t_mlx *d)
{
	if (d->k->w)
		upkey(d, &d->r);
	if (d->k->s)
		downkey(d, &d->r);
	if (d->k->d)
		rightkey(d, &d->r);
	if (d->k->a)
		leftkey(d, &d->r);
	if (d->k->ra)
		rotate_right(&d->r);
	if (d->k->la)
		rotate_left(&d->r);
	raycast(d, &d->r);
	return (0);
}
