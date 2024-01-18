/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsC.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:39:02 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/18 19:21:15 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	l_issp(char	*map)
{
	int	i;

	i = 0;
	while (map[i] == ' ' || map[i] == '\t')
		i++;
	if (!map[i] || *map == '\n')
		return (true);
	return (false);
}

void	free_nodes(t_nodes **nodes, t_pos mlw, int index)
{
	if (!index)
	{
		while (index != mlw.y)
			free(nodes[index++]);
	}
	else
	{
		while (index)
		{
			free(nodes[index]);
			index--;
		}	
	}
	free(nodes);
	nodes = NULL;
}

t_pos	get_mlw(char **map)
{
	int		len;
	t_pos	p;
	int		t;

	len = 0;
	p.y = -1;
	while (map[++p.y])
	{
		p.x = -1;
		t = 0;
		while (map[p.y][++p.x])
			if (map[p.y][p.x] == 9)
				t++;
		if (len < p.x || (t && (p.x + (3 * t)) > len))
		{
			if (t && (p.x + (3 * t)) > len)
				len = p.x + (3 * t);
			else
				len = p.x;
		}
	}
	return ((t_pos){len, p.y});
}

void	set_node(t_nodes *n, bool s, bool w, t_pos p)
{
	n->p.y = p.y;
	n->p.x = p.x;
	n->s = s;
	n->w = w;
	n->visited = false;
	(void)n;
}
