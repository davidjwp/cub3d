/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:25:03 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/29 16:44:29 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_nodes(t_n **nodes, t_pos mlw, int index)
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

static t_pos	get_mlw(char **map)
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

static void	set_node(t_n *n, t_n set)
{
	n->p.y = set.p.y;
	n->p.x = set.p.x;
	n->s = set.s;
	n->w = set.w;
	n->c = set.c;
	n->visited = false;
	(void)n;
}

static void	setn_line(t_n **nl, char *line, t_pos p, int len)
{
	int	i;
	int	tmp;
	int	l;

	i = -1;
	l = ft_strlen(line);
	while (++p.x < len)
	{
		while (++i < l && line[i] == '\t')
		{
			tmp = 4 + p.x--;
			while (&(nl[0][++p.x]) != &(nl[0][tmp]))
				set_node(&(nl[0][p.x]), (t_n){p, false, true, false, false});
		}
		if (i < l && line[i] == '1')
			set_node(&(nl[0][p.x]), (t_n){p, true, false, false, false});
		else if (i < l && line[i] == '0')
			set_node(&(nl[0][p.x]), (t_n){p, false, false, false, false});
		else if (i < l && ischar(line[i]))
			set_node(&(nl[0][p.x]), (t_n){p, false, false, true, false});
		else
			set_node(&(nl[0][p.x]), (t_n){p, false, true, false, false});
	}
}

bool	cr_nodes(t_mdata *fdata)
{
	t_n		**nodes;
	t_pos	p;
	int		l;

	p = get_mlw(fdata->map);
	fdata->mlw = p;
	l = p.x;
	nodes = malloc(sizeof(t_n *) * (p.y + 1));
	if (!nodes)
		return (err_msg("cr_nodes malloc fail"));
	nodes[p.y] = NULL;
	while (--p.y >= 0)
	{
		p.x = -1;
		nodes[p.y] = malloc(sizeof(t_n) * (l + 1));
		if (!nodes[p.y])
			return (free_nodes(nodes, fdata->mlw, p.y), err_msg("i crn fail"));
		setn_line(&nodes[p.y], fdata->map[p.y], (t_pos){-1, p.y}, fdata->mlw.x);
	}
	fdata->m_nodes = nodes;
	return (true);
}
