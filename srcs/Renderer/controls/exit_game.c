/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:35:25 by ael-malt          #+#    #+#             */
/*   Updated: 2024/02/06 22:24:50 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	close_win(int key, void *param)
{
	t_mlx	*d;

	d = (t_mlx *)param;
	if (key == XK_Escape)
	{
		mlx_loop_end(d->mlx);
		mlx_destroy_window(d->mlx, d->win);
		d->win = NULL;
	}
	return (0);
}
