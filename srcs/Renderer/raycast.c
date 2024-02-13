/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:49:44 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 11:00:16 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	raycalc(t_mlx *d, t_ray *r, int x)
{
	rayinit(x, r);
	stepcal(r);
	raydda(d, r);
	if (r->side == 0)
		r->perpwalldist = (r->sdist.y - r->ddist.y);
	else
		r->perpwalldist = (r->sdist.x - r->ddist.x);
	if (r->perpwalldist != 0)
		r->lineheight = (int)(HEIGHT / r->perpwalldist);
	else
		r->lineheight = HEIGHT;
	r->drawstart = -(r->lineheight) / 2 + HEIGHT / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + HEIGHT / 2;
	if (r->drawend >= HEIGHT)
		r->drawend = HEIGHT - 1;
	if (r->side == 0)
		r->wallx = r->pos.x + r->perpwalldist
			* r->raydir.x;
	else
		r->wallx = r->pos.y + r->perpwalldist
			* r->raydir.y;
	r->wallx -= floor(r->wallx);
}

t_xpms	get_current_oriented_texture(t_mlx *d, t_ray *r)
{
	if (r->side == 1)
	{
		if (r->raydir.x > 0)
			return (d->xpms[WE]);
		else
			return (d->xpms[EA]);
	}
	else
	{
		if (r->raydir.y > 0)
			return (d->xpms[NO]);
		else
			return (d->xpms[SO]);
	}
}

void	set_texture_data(t_mlx *d, t_ray *r)
{
	r->current_xpm = get_current_oriented_texture(d, r);
	r->tex.x = (int)(r->wallx * (double)r->current_xpm.imgw);
	if (r->side == 0 && r->raydir.y > 0)
		r->tex.x = r->current_xpm.imgw - r->tex.x - 1;
	if (r->side == 1 && r->raydir.x < 0)
		r->tex.x = r->current_xpm.imgw - r->tex.x - 1;
	r->drawstep = 1.0 * r->current_xpm.imgh / r->lineheight;
	r->texpos = (r->drawstart - (double)HEIGHT / 2
			+ (double)r->lineheight / 2) * r->drawstep;
}

void	raycast(t_mlx *d, t_ray *r)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		raycalc(d, r, x);
		set_texture_data(d, r);
		caldrawstrip(d, r, x);
	}
	minimap(d, r);
	swap_buffers(d);
}
