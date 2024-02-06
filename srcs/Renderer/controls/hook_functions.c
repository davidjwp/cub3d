/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:30:37 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/06 22:24:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	mouse(int mouseX, int mouseY, t_mlx *d)
{
	(void) mouseY;
	if (d->k->mouse == true)
	{
		if (mouseX > WIDTH / 2)
			rotate_right(&d->r);
		if (mouseX < WIDTH / 2)
			rotate_left(&d->r);
		mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

int	key_press(int key, void *param)
{
	t_mlx	*d;

	d = (t_mlx *)param;
	if (key == XK_Escape)
		return (close_win(key, param), 0);
	if (key == 'w')
		d->k->w = true;
	if (key == 'a')
		d->k->a = true;
	if (key == 's')
		d->k->s = true;
	if (key == 'd')
		d->k->d = true;
	if (key == 'p')
		d->k->p = true;
	if (key == XK_Left)
		d->k->la = true;
	if (key == XK_Right)
		d->k->ra = true;
	if ((key == 65513 || key == 65507) && d->k->mouse == false)
		d->k->mouse = true;
	else if ((key == 65513 || key == 65507) && d->k->mouse == true)
		d->k->mouse = false;
	return (0);
}

// Update this function to unset the key flags
int	key_release(int key, void *param)
{
	t_mlx	*d;

	d = (t_mlx *)param;
	if (key == 'w')
		d->k->w = false;
	if (key == 'a')
		d->k->a = false;
	if (key == 's')
		d->k->s = false;
	if (key == 'd')
		d->k->d = false;
	if (key == 'p')
		d->k->p = false;
	if (key == XK_Left)
		d->k->la = false;
	if (key == XK_Right)
		d->k->ra = false;
	return (0);
}
