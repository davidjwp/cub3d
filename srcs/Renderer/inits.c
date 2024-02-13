/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:22:10 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/12 11:23:30 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_raycast(t_mlx *d, t_pos cpos)
{
	t_ray	ray;

	ray.pos.x = cpos.x + 0.5;
	ray.pos.y = cpos.y + 0.5;
	if (d->pl_sp_dir == 'N')
	{
		ray.dir = (t_p){0.0, -1.0};
		ray.plane = (t_p){0.66, 0.0};
	}
	if (d->pl_sp_dir == 'S')
	{
		ray.dir = (t_p){0.0, 1.0};
		ray.plane = (t_p){-0.66, 0.0};
	}
	if (d->pl_sp_dir == 'E')
	{
		ray.dir = (t_p){1.0, 0.0};
		ray.plane = (t_p){0.0, 0.66};
	}
	if (d->pl_sp_dir == 'W')
	{
		ray.dir = (t_p){-1.0, 0.0};
		ray.plane = (t_p){0.0, -0.66};
	}
	d->r = ray;
}

bool	init_render(t_mlx *d, t_mdata *fdata)
{
	d->map = fdata->map;
	d->pl_sp_dir = fdata->pl_sp_dir;
	d->mxy = fdata->mlw;
	d->k = malloc(sizeof(t_key));
	if (!d->k)
		return (err_msg("init key malloc fail"));
	d->k->w = false;
	d->k->s = false;
	d->k->d = false;
	d->k->a = false;
	d->k->ra = false;
	d->k->la = false;
	d->k->mouse = true;
	d->i = malloc(sizeof(t_img));
	if (!d->i)
		return (free(d->k), err_msg("init img malloc fail"));
	d->i3d = malloc(sizeof(t_img));
	if (!d->i3d)
		return (free(d->k), free(d->i), err_msg("init 3Dimg malloc fail"));
	return (true);
}

void	init_hooks(t_mlx *d)
{
	mlx_hook(d->win, KeyPress, KeyPressMask, key_press, d);
	mlx_hook(d->win, KeyRelease, KeyReleaseMask, key_release, d);
	mlx_hook(d->win, DestroyNotify, StructureNotifyMask, close_win, d);
	mlx_hook(d->win, MotionNotify, PointerMotionMask, mouse, d);
	mlx_loop_hook(d->mlx, buttons, d);
}
