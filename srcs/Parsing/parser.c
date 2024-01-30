/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:21:47 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/30 15:33:53 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	int		i;

	i = 0;
	l = NULL;
	current = NULL;
	if (!cr_nodes(fdata))
		return (false);
	if (!find_nchar(&current, fdata, &fdata->cpos))
		return (false);
	if (!av_node(&l, fdata->m_nodes, current, fdata->mlw))
		return (free_lst(l), false);
	while (l != NULL)
	{
		current = l->node;
		current->visited = true;
		rm_visited(&l);
		if (!av_node(&l, fdata->m_nodes, current, fdata->mlw))
			return (tty_print(fdata, l, current, i++), free_lst(l));
		tty_print(fdata, l, current, i++);
	}
	free_lst(l);
	return (true);
}

bool	file_parse(char **split, const char *file_name, t_mdata *fdata)
{
	if (split == NULL)
		return (err_msg("split fail"));
	fdata->map = split;
	if (ft_strncmp(ft_strchr(file_name, '.'), ".cub", 5))
		return (err_msg("Bad extension"));
	if (!texcol_check(fdata, -1, 0))
		return (err_msg("Bad texcol"));
	if (!cr_map(fdata))
		return (false);
	if (!is_open(fdata))
		return (false);
	return (true);
}
