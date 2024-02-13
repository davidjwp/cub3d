/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycalc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:59:36 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/12 11:02:09 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rayinit(int x, t_ray *r)
{
	r->hit = false;
	r->camera.x = 2 * x / (double)WIDTH - 1;
	r->raydir.x = r->dir.x + r->plane.x * r->camera.x;
	r->raydir.y = r->dir.y + r->plane.y * r->camera.x;
	r->map.x = (int)r->pos.x;
	r->map.y = (int)r->pos.y;
	r->ddist.x = fabs(1 / r->raydir.x);
	r->ddist.y = fabs(1 / r->raydir.y);
}

void	stepcal(t_ray *r)
{
	if (r->raydir.x < 0)
	{
		r->step.x = -1;
		r->sdist.x = (r->pos.x - r->map.x) * r->ddist.x;
	}
	else
	{
		r->step.x = 1;
		r->sdist.x = (r->map.x + 1.0 - r->pos.x) * r->ddist.x;
	}
	if (r->raydir.y < 0)
	{
		r->step.y = -1;
		r->sdist.y = (r->pos.y - r->map.y) * r->ddist.y;
	}
	else
	{
		r->step.y = 1;
		r->sdist.y = (r->map.y + 1.0 - r->pos.y) * r->ddist.y;
	}
}

void	raydda(t_mlx *d, t_ray *r)
{
	while (!r->hit)
	{
		if (r->sdist.y < r->sdist.x)
		{
			r->sdist.y += r->ddist.y;
			r->map.y += r->step.y;
			r->side = false;
		}
		else
		{
			r->sdist.x += r->ddist.x;
			r->map.x += r->step.x;
			r->side = true;
		}
		if (d->map[r->map.y][r->map.x] == '1')
			r->hit = true;
	}
}
