/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_utilsC.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:39:02 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/30 15:49:39 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

bool	free_lst(t_lst *l)
{
	t_lst	*f;

	if (!l)
		return (false);
	while (l->next != NULL)
	{
		f = l;
		l = l->next;
		free(f);
	}
	free(l);
	return (false);
}

bool	find_nchar(t_n **start, t_mdata *f, t_pos *p)
{
	int		n;

	n = 0;
	while (++p->y < f->mlw.y)
	{
		while (++p->x < f->mlw.x)
		{
			if (f->m_nodes[p->y][p->x].c)
			{
				*start = &f->m_nodes[p->y][p->x];
				n++;
			}
		}
		p->x = -1;
	}
	if (n > 1)
		return (err_msg("too many characters"));
	(*start)->visited = true;
	*p = (*start)->p;
	return (true);
}

bool	n_open(t_n **node, t_pos p, t_pos mlw)
{
	if (p.y + 1 >= mlw.y || p.y - 1 < 0 || p.x + 1 >= mlw.x || p.x - 1 < 0)
		return (true);
	if (node[p.y + 1][p.x].s || \
	node[p.y - 1][p.x].s || \
	node[p.y][p.x + 1].s || \
	node[p.y][p.x - 1].s)
		return (true);
	return (false);
}
