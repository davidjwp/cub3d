/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:17:57 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/20 23:11:05 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **split)
{
	for(int y = 0, i = 0; split[y]; y++){
		for(; split[y][i]; i++)
			split[y][i] == '\t' ? write (1, "    ", 4) : write (1, &split[y][i], 1);
		i = 0;
		if (split[y][i] != '\n')
			write (1, "\n", 1);
	}	
}

static void	_pNode(t_n node)
{
	if (node.visited)
		write (1, "\033[102m \033[0m", 11);
	else if (node.c)
		write (1, "C", 1);
	else if (node.s)
		write (1, " ", 1);
	else if (node.w)
		write (1, "\033[107m \033[0m", 11);
	else 
		write (1, " ", 1);
}

void	PrintNodes(t_mdata *f)
{
	for (int i = 0; i <= f->mlw.y; i++)
		for(int y = 0; y <= f->mlw.x && f->m_nodes[i] != NULL; y++)
			y == f->mlw.x ? write (1, "\n", 1) : _pNode(f->m_nodes[i][y]);
}

static bool	print_lst(t_lst *l)
{
	t_lst	*tmp;
	bool	v;

	v = false;
	if (!l)
		return (true);
	tmp = l;
	write (1, "\n", 1);
	while (tmp->next != NULL)
	{
		_pNode(*tmp->node);
		if (tmp->node->visited)
			v = true;
		tmp = tmp->next;
	}
	_pNode(*tmp->node);
	if (tmp->node->visited)
		v = true;
	if (v)
		return (write (1, "\n",1), false);
	return (write (1, "\n",1), true);
}

void	tty_print(t_mdata *f, t_lst *l, t_n *c, int i)
{
	unsigned long area = (unsigned long)f->mlw.x * (unsigned long)f->mlw.y;
	unsigned long sleep_time = 1000000000 / (area > 0 ? area : 1);
	
	unsigned long max_sleep_time = 40000;
	if (sleep_time > max_sleep_time) {
	    sleep_time = max_sleep_time;
	}
	
	usleep((useconds_t)sleep_time);
	//usleep(((f->mlw.x * f->mlw.y) / 10) * 500); other timer
	write (1, "\033[2J",5);
	write (1, "\033[H", 4);
	PrintNodes(f);
	print_lst(l);
	printf("current node: (%i,%i)\n", c->p.y, c->p.x);
	printf ("\nstep %i\n", i++);
}