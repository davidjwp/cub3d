/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsB.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:03:39 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/16 19:53:26 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	is_texcol(int pos, t_mdata *fdata)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (pos == fdata->tc_index[i])
			return (true);
	return (false);
}

bool	find_char(t_mdata *fdata, t_pos *p)
{
	while (fdata->map[++p->y] != NULL)
	{
		while (fdata->map[p->y][++p->x])
			if (ischar(fdata->map[p->y][p->x]) && !is_texcol(p->y, fdata))
				return (true);
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
	int		i;

	i = -1;
	if (!find_char(fdata, p))
		return (-1);
	len = p->y;
	while (l_ismap(fdata->map[len]))
		len++;
	while (fdata->map[p->y][++p->x])
	{
		if (l_ismap(fdata->map[p->y]))
		{
			p->y--;
			p->x = -1;
		}
		else
			break ;
	}
	while (++i < 6)
		if (fdata->tc_index[i] > p->y + 1)
			return (err_msg("Wrong texture placement"), -1);
	return (len - p->y);
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
