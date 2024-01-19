/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:21:47 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/19 22:39:59 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setn_line(t_n **nl, char *line, t_pos p, int len)
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
			tmp =  4 + p.x--;
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
	t_n	**nodes;
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

bool	add_lst(t_lst **l, t_n *node)
{
	t_lst	*tmp;
	t_lst	*add;

	tmp = *l;
	while (tmp->next != NULL)
		tmp = tmp->next;
	add = malloc(sizeof(t_lst));
	if (!add)
		return (err_msg("add_lst malloc fail"));
	add->next = NULL;
	add->node = node;
	tmp->next = add;
	return (true);
}

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
		return (err_msg("too many characterss"));
	(*start)->visited = true;
	return (true);
}

bool	n_open(t_n **node, t_pos p, t_pos mlw)
{
	if (p.y + 1 >= mlw.y || p.y - 1 <= 0 || p.x + 1 >= mlw.x || p.x - 1 <= 0)
		return (true);
	if (node[p.y + 1][p.x].s || \
	node[p.y - 1][p.x].s || \
	node[p.y][p.x + 1].s || \
	node[p.y][p.x - 1].s)
		return (true);
	return (false);
}

bool	av_node(t_lst **l, t_n **node, t_pos mlw)
{
	if (n_open(node, (*l)->node->p, mlw))
		return (err_msg("map is open"));
	if (!node[(*l)->node->p.y + 1][(*l)->node->p.x].w && \
	!node[(*l)->node->p.y + 1][(*l)->node->p.x].visited)
		add_lst(l, &node[(*l)->node->p.y + 1][(*l)->node->p.x]);
	if (!node[(*l)->node->p.y - 1][(*l)->node->p.x].w && \
	!node[(*l)->node->p.y - 1][(*l)->node->p.x].visited)
		add_lst(l, &node[(*l)->node->p.y - 1][(*l)->node->p.x]);
	if (!node[(*l)->node->p.y][(*l)->node->p.x - 1].w && \
	!node[(*l)->node->p.y][(*l)->node->p.x - 1].visited)
		add_lst(l, &node[(*l)->node->p.y][(*l)->node->p.x - 1]);
	if (!node[(*l)->node->p.y][(*l)->node->p.x + 1].w && \
	!node[(*l)->node->p.y][(*l)->node->p.x + 1].visited)
		add_lst(l, &node[(*l)->node->p.y][(*l)->node->p.x + 1]);
	return (true);
}

static bool	cr_lst(t_lst **l, t_n **start)
{
	l = malloc(sizeof(t_lst *));
	if (!l)
		return (err_msg("lst malloc fail"));
	*l = malloc(sizeof(t_lst));
	if (!(*l))
		return (err_msg("*lst malloc fail"));
	(*l)->next = NULL;
	(*l)->node = *start;
	return (true);
}

void	rem_l(t_lst **lst)
{
	t_lst	*tmp;

	tmp = (*lst)->next;
	free()
}

bool	is_open(t_mdata *fdata)
{
	t_n		*current;
	t_lst	*l;
	t_pos	p;

	p = (t_pos){-1, -1};
	current = NULL;
	if (!cr_nodes(fdata))
		return (false);
	if (!find_nchar(&current, fdata))
		return (false);
	if (!cr_lst(&l, &current))
		return (false);
	while (l != NULL && !(*l).node->visited)
	{
		av_node(&l, fdata->m_nodes, fdata->mlw);
		current = l->node;
		current->visited = true;
		
	}
	//PrintNodes(fdata);
	return (true);
}

//check if there are multiple characters in the map
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
		return (err_msg("Map is open"));
	//print_map(fdata->map);
	return (true);
}

int	main(void)
{
	t_mdata		fdata;
	const char	*file_name;
	int			fd;
	char		*buf;

	/*			initialization			*/
	fdata = (t_mdata){NULL, NULL, NULL, {0, 0, 0, 0, 0, 0}, {0, 0}};
	fdata.tex = malloc(sizeof(char *) * 7);
	if (!fdata.tex)
		return (err_msg("malloc fail"), -1);
	for (int i = 0; i < 6; i++){
		fdata.tex[i] = malloc(sizeof(char) * BUF_SIZ);
		if (!fdata.tex[i])
			return (err_msg("malloc fail"), free_split(fdata.tex, i), -1);
		*fdata.tex[i] = 0;
	}
	fdata.tex[6] = NULL;
	file_name = "Map.cub";
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (err_msg("open fail"), 1);
	if (gnl(fd, &buf, 0, 0))
		return (err_msg("gnl error"), close(fd), 2);
	if (buf == NULL)
		return (err_msg("gnl fail"), close(fd), 3);
	/*			parsing					*/
	if (file_parse(ft_split(buf, '\n'), file_name, &fdata))
		printf("\033[102mgood Map\033[0m\n");
	else
		printf("\033[101mbad Map\033[0m\n");
	/*			cleaning up				*/
	clean_all(buf, fdata, fd);
	return (0);
}
