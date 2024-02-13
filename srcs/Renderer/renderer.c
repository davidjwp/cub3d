/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 15:00:07 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_images(t_mlx *data)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		data->i->img[i] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT);
		data->i->add[i] = mlx_get_data_addr(data->i->img[i], &data->i->bpp, \
		&data->i->len, &data->i->end);
	}
	data->i->current = 0;
}

/*
	this function will first calculate the beginning and end of the strip in 
	y coordinates along the x axis, if the strip starts within the height of
	the screen and not at the start like 0 then you draw the ceiling until
	the start of the strip then you draw the strip and draw the floor like the
	ceiling
*/

void	caldrawstrip(t_mlx *d, t_ray *r, int x)
{
	int	color;

	color = 0;
	if (r->drawstart > 0)
		drawstrip(d->i, x, (int [2]){0, r->drawstart}, d->col[1]);
	while (r->drawstart < r->drawend)
	{
		r->tex.y = (int)r->texpos & (r->current_xpm.imgh - 1);
		r->texpos += r->drawstep;
		color = ((int *)r->current_xpm.add)[r->current_xpm.imgh
			* r->tex.y + abs(r->tex.x)];
		pixput(d->i, x, r->drawstart, color);
		r->drawstart++;
	}
	if (r->drawend < HEIGHT && r->drawend > 0)
		drawstrip(d->i, x, (int [2]){r->drawend, HEIGHT}, d->col[0]);
}

void	drawplayer(t_mlx *d, int x, int y)
{
	t_p	s;
	t_p	e;

	s = (t_p){0, 0};
	e = (t_p){s.x + 8, s.y + 8};
	while (s.y < e.y)
	{
		while (s.x < e.x)
		{
			pixput(d->i, x + s.x, y + s.y, YELLOW);
			s.x++;
		}
		s.x = 0;
		s.y++;
	}
}

void	destroy_all(t_mlx *m, bool xpms)
{
	int	i;

	i = -1;
	mlx_destroy_window(m->mlx, m->win);
	m->win = NULL;
	while (++i < 2)
		mlx_destroy_image(m->mlx, m->i->img[i]);
	i = -1;
	if (xpms)
		while (++i < 4)
			mlx_destroy_image(m->mlx, m->xpms[i].img);
	mlx_destroy_display(m->mlx);
	free(m->mlx);
	free(m->k);
	free(m->i);
	free(m->i3d);
}

int	start_renderer(t_mdata *fdata)
{
	t_mlx	d;

	if (!init_render(&d, fdata))
		return (-1);
	init_raycast(&d, fdata->cpos);
	d.mlx = mlx_init();
	if (!d.mlx)
		return (0);
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	if (!d.win)
		return (0);
	init_images(&d);
	if (!xpm_check(fdata, &d, d.mlx))
		return (err_msg("Bad textures"), destroy_all(&d, false), -1);
	if (!col_check(fdata))
		return (err_msg("Bad colours"), destroy_all(&d, true), -1);
	d.col[0] = fdata->col[0];
	d.col[1] = fdata->col[1];
	mlx_mouse_hide(d.mlx, d.win);
	init_hooks(&d);
	mlx_loop(d.mlx);
	destroy_all(&d, true);
	return (0);
}
