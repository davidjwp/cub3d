/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:07:46 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/04 20:11:54 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	linelen(char *line)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (line[++i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
	}
	return (len);
}

static void	linecpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	y;
	int				tab;

	i = 0;
	y = i;
	if (!src || !dst)
		return ;
	if (size)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			if (src[i] == '\t')
			{
				tab = 4;
				while (tab--)
					dst[y++] = ' ';
				i++;
			}
			else
				dst[y++] = src[i++];
		}
		dst[y] = '\0';
	}
}

/*
	create the map in fdata

	starts searching the map from the position of the last color of texture
*/
bool	cr_map(t_mdata *fdata)
{
	char	**tmp;
	int		len;
	t_pos	p;
	int		i;

	i = -1;
	p = (t_pos){-1, -1};
	len = find_map(fdata, &p) + 1;
	if (p.y < 0 || p.y < find_highest(fdata->tc_index))
		return (false);
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (err_msg("cr_map malloc fail"));
	tmp[len - 1] = NULL;
	while (--len)
	{
		tmp[++i] = malloc(sizeof(char) * (linelen(fdata->map[p.y]) + 1));
		if (!tmp[i])
			return (free_split(tmp, i), err_msg("cr_map index malloc fail"));
		linecpy(tmp[i], fdata->map[p.y], linelen(fdata->map[p.y]) + 1);
		p.y++;
	}
	return (free_split(fdata->map, 0), fdata->map = tmp, true);
}
