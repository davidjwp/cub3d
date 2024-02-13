/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer_utilsA.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:58:40 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 15:01:56 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	outmap(t_pos start, t_minline mini)
{
	if (start.x < mini.limitx.x || \
		start.x >= mini.limitx.y - 1 || \
		start.y < mini.limity.x || \
		start.y >= mini.limity.y - 1)
		return (true);
	return (false);
}

void	swap_buffers(t_mlx *data)
{
	if (data->win != NULL)
		mlx_put_image_to_window(data->mlx, data->win, \
		data->i->img[data->i->current], 0, 0);
	data->i->current = !data->i->current;
	mlx_destroy_image(data->mlx, data->i->img[data->i->current]);
	data->i->img[data->i->current] = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->i->add[data->i->current] = mlx_get_data_addr(data->i->img[data->i->\
	current], &data->i->bpp, &data->i->len, &data->i->end);
}

void	pixput(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && color != -1)
	{
		dst = i->add[i->current] + (y * i->len + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	drawstrip(t_img *i, int x, int *y, int color)
{
	while (y[0] < y[1])
	{
		pixput(i, x, y[0], color);
		y[0]++;
	}
}
