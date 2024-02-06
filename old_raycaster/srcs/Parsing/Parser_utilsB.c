/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_utilsB.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:03:39 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/30 15:49:48 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	gnl(int fd, char **str, int i, int n)
{
	char	*buf;
	char	c;

	buf = malloc(sizeof(char) * BUF_SIZ);
	if (buf == NULL)
		return (*str = NULL, 1);
	n = read(fd, &c, 1);
	if (n == 0 || n == -1)
		return (free(buf), err_msg("gnl read fail"), *str = NULL, 2);
	while (c == '\n')
		n = read(fd, &c, 1);
	if (n)
		buf[i++] = c;
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (i == BUF_SIZ - 1)
			break ;
		if (n != 0)
			buf[i] = c;
		i++;
	}
	buf[i - 1] = 0;
	buf[BUF_SIZ - 1] = 0;
	return (*str = buf, 0);
}

/*
*	finds the character from the position of the last texture or color
*/
static bool	find_char(t_mdata *fdata, t_pos *p, int hp)
{
	while ((&fdata->map[hp])[++p->y] != NULL)
	{
		if (l_ismap((&fdata->map[hp])[p->y]))
			while ((&fdata->map[hp])[p->y][++p->x])
				if (ischar((&fdata->map[hp])[p->y][p->x]))
					return (p->y += hp, true);
		p->x = -1;
	}
	return (false);
}

/*
*	finds the map using the character placement
*/
int	find_map(t_mdata *fdata, t_pos *p)
{
	int		len;

	if (!find_char(fdata, p, find_highest(fdata->tc_index)))
		return (err_msg("no character"), p->y = -1, -1);
	len = p->y;
	while (l_ismap(fdata->map[len]))
		len++;
	while (l_ismap(fdata->map[p->y]))
		p->y--;
	p->y++;
	return ((len - p->y));
}

bool	is_full(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL && *map[i])
		if (++i == 6)
			return (true);
	return (false);
}

int	find_highest(int *index)
{
	int	highest;
	int	y;
	int	i;

	y = -1;
	i = -1;
	highest = 0;
	while (++y < 2)
		while (++i < 6)
			if (index[i] > highest)
				highest = index[i];
	return (highest);
}
