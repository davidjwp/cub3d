/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:42:18 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/06 22:25:09 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	rotate_left(t_ray *r)
{
	double	olddirx;
	double	oldplanex;

	olddirx = r->dir.x;
	r->dir.x = r->dir.x * cos(-RS) - r->dir.y * sin(-RS);
	r->dir.y = olddirx * sin(-RS) + r->dir.y * cos(-RS);
	oldplanex = r->plane.x;
	r->plane.x = r->plane.x * cos(-RS) - r->plane.y * sin(-RS);
	r->plane.y = oldplanex * sin(-RS) + r->plane.y * cos(-RS);
}

void	rotate_right(t_ray *r)
{
	double	olddirx;
	double	oldplanex;

	olddirx = r->dir.x;
	r->dir.x = r->dir.x * cos(RS) - r->dir.y * sin(RS);
	r->dir.y = olddirx * sin(RS) + r->dir.y * cos(RS);
	oldplanex = r->plane.x;
	r->plane.x = r->plane.x * cos(RS) - r->plane.y * sin(RS);
	r->plane.y = oldplanex * sin(RS) + r->plane.y * cos(RS);
}
// void	rotate_right(t_mlx *d)
// {
// 	d->pl->pa += RS;
// 	d->pl->pa = fix_ang(d->pl->pa);
// 	d->pl->pdx = d->pl->px + LINE * cos(degtorad(d->pl->pa));
// 	d->pl->pdy = d->pl->py + LINE * sin(degtorad(d->pl->pa));
// }

// void	rotate_left(t_mlx *d)
// {
// 	d->pl->pa -= RS;
// 	d->pl->pa = fix_ang(d->pl->pa);
// 	d->pl->pdx = d->pl->px + LINE * cos(degtorad(d->pl->pa));
// 	d->pl->pdy = d->pl->py + LINE * sin(degtorad(d->pl->pa));
// }
