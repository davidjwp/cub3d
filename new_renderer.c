/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/06 21:55:24 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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

	color = GREEN;
	if (r->side)
		color /= 2;
	r->drawstart = -r->lineheight / 2 + HEIGHT / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + HEIGHT / 2;
	if (r->drawend >= HEIGHT)
		r->drawend = HEIGHT - 1;
	if (r->drawstart > 0)
		drawstrip(d->i, x, (int [2]){0, r->drawstart}, d->col[1]);
	while (r->drawstart < r->drawend)
	{
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

void	destroyAll(t_mlx *m)
{
	int	i;

	i = -1;
	while (++i < 2)
		mlx_destroy_image(m->mlx, m->i->img[i]);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(m->mlx, m->xpms[i].img);
	mlx_destroy_display(m->mlx);
	free(m->mlx);
	free(m->k);
	free(m->i);
	free(m->i3d);
}

static void	init_raycast(t_mlx *d, t_pos cpos)
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

static bool	init_render(t_mlx *d, t_mdata *fdata)
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

int	start_renderer(t_mdata *fdata)
{
	t_mlx	d;

	if (!init_render(&d, fdata))
		return (-1);
	init_raycast(&d, fdata->cpos);
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	init_images(&d);
	if (!xpm_check(fdata, &d, d.mlx))
		return (err_msg("Bad textures"), mlx_destroy_display(d.mlx), \
		free(d.mlx),free(d.i),free(d.i3d),free(d.k), -1);
	if (!col_check(fdata))
		return (mlx_destroy_display(d.mlx), free(d.mlx), free(d.i), \
		free(d.i3d), free(d.k), -1);
	d.col[0] = fdata->col[0];
	d.col[1] = fdata->col[1];
	// mlx_mouse_hide(d.mlx, d.win);//here
	mlx_hook(d.win, KeyPress, KeyPressMask, key_press, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, key_release, &d);
	mlx_hook(d.win, MotionNotify, PointerMotionMask, mouse, &d);
	mlx_loop_hook(d.mlx, buttons, &d);
	mlx_loop(d.mlx);
	destroyAll(&d);
	return (0);
}
