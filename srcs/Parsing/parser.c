/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:21:47 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/23 15:53:24 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	find_nchar(t_n **start, t_mdata *f)
{
	t_pos	p;
	int		n;

	n = 0;
	p = (t_pos){-1, -1};
	while (++p.y < f->mlw.y)
	{
		while (++p.x < f->mlw.x)
		{
			if (f->m_nodes[p.y][p.x].c)
			{
				*start = &f->m_nodes[p.y][p.x];
				n++;
			}
		}
		p.x = -1;
	}
	if (n > 1)
		return (err_msg("too many characters"));
	(*start)->visited = true;
	return (true);
}

bool	add_lst(t_lst **l, t_n *node)
{
	t_lst	*tmp;
	t_lst	*add;

	tmp = *l;
	if (!tmp)
	{
		*l = malloc(sizeof(t_lst));
		if (!(*l))
			return (err_msg("add_lst malloc fail"));
		(*l)->next = NULL;
		(*l)->node = &(*node);
		return (true);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	add = malloc(sizeof(t_lst));
	if (!add)
		return (err_msg("add_lst malloc fail"));
	add->next = NULL;
	add->node = &(*node);
	tmp->next = add;
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

bool	av_node(t_lst **l, t_n **node, t_n *current, t_pos mlw)
{
	if (n_open(node, current->p, mlw))
		return (err_msg("map is open"));
	if (!node[current->p.y + 1][current->p.x].w && \
	!node[current->p.y + 1][current->p.x].visited)
		add_lst(l, &node[current->p.y + 1][current->p.x]);
	if (!node[current->p.y - 1][current->p.x].w && \
	!node[current->p.y - 1][current->p.x].visited)
		add_lst(l, &node[current->p.y - 1][current->p.x]);
	if (!node[current->p.y][current->p.x - 1].w && \
	!node[current->p.y][current->p.x - 1].visited)
		add_lst(l, &node[current->p.y][current->p.x - 1]);
	if (!node[current->p.y][current->p.x + 1].w && \
	!node[current->p.y][current->p.x + 1].visited)
		add_lst(l, &node[current->p.y][current->p.x + 1]);
	return (true);
}

void	rm_visited(t_lst **l)
{
	t_lst	*tmp;
	t_lst	*prev;
	t_lst	*f;

	tmp = *l;
	prev = NULL;
	while (tmp != NULL)
	{
		if (tmp->node->visited)
		{
			f = tmp;
			if (prev != NULL)
				prev->next = tmp->next;
			else
				*l = tmp->next;
			tmp = tmp->next;
			free(f);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

bool	is_open(t_mdata *fdata)
{
	t_n		*current;
	t_lst	*l;

	l = NULL;
	current = NULL;
	if (!cr_nodes(fdata))
		return (false);
	if (!find_nchar(&current, fdata))
		return (false);
	if (!av_node(&l, fdata->m_nodes, current, fdata->mlw))
		return (free_lst(l), false);
	int	i = 0;//test here
	while (l != NULL)
	{
		current = l->node;
		current->visited = true;
		rm_visited(&l);
		if (!av_node(&l, fdata->m_nodes, current, fdata->mlw)){
			tty_print(fdata, l, current, i++);//test here
			return (free_lst(l));
		}
		tty_print(fdata, l, current, i++);//test here
	}
	free_lst(l);
	return (true);
}

//wait until we agree on the structures to make this
//i'm not sure how to initialize the textures so this might be wrong
//bool	texcolval_check(t_mdata *fdata)
//{
//	fdata->texcol[NO] = mlx_xpm_file_to_image(fdata->)
//	return (image_check(fdata));
//}

//check if there are multiple characters in the map
//check the values of FLOOR and CEILING
//check that the textures address is correct
bool	file_parse(char **split, const char *file_name, t_mdata *fdata)
{
	if (split == NULL)
		return (err_msg("split fail"));
	fdata->map = split;
	if (ft_strncmp(ft_strchr(file_name, '.'), ".cub", 5))
		return (err_msg("Bad extension"));
	if (!texcol_check(fdata, -1, 0))
		return (err_msg("Bad texcol"));
	//if (!texcolval_check(fdata))
	//	return (err_msg("Bad texcol values"));
	if (!cr_map(fdata))
		return (false);
	if (!is_open(fdata))
		return (false);
	return (true);
}