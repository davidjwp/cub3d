/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:17:57 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 15:02:47 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_pnode(t_n node)
{
	if (node.c)
		write (1, "\033[101m \033[0m", 11);
	else if (node.visited)
		write (1, "\033[102m \033[0m", 11);
	else if (node.s)
		write (1, " ", 1);
	else if (node.w)
		write (1, "\033[107m \033[0m", 11);
	else
		write (1, "0", 1);
}

static void	print_nodes(t_mdata *f)
{
	t_pos	p;

	p = (t_pos){-1, -1};
	while (++p.y <= f->mlw.y)
	{
		while (++p.x <= f->mlw.x && f->m_nodes[p.y] != NULL)
		{
			if (p.x == f->mlw.x)
				write (1, "\n", 1);
			else
				_pnode(f->m_nodes[p.y][p.x]);
		}
		p.x = -1;
	}
}

static void	print_lst(t_lst *l)
{
	t_lst	*tmp;
	int		i;

	i = -1;
	if (!l)
		return ;
	tmp = l;
	write (1, "\n", 1);
	while (++i < 50)
		write (1, " ", 1);
	write (1, "\r", 2);
	while (tmp->next != NULL)
	{
		_pnode(*tmp->node);
		tmp = tmp->next;
	}
	_pnode(*tmp->node);
	write (1, "\n", 2);
}

static void	p_step_node(int i, t_n *c)
{
	char	*y;
	char	*x;
	char	*step;

	write (1, "current node: (", 16);
	y = ft_itoa(c->p.y);
	if (!y)
		return ;
	write (1, y, ft_strlen(y));
	free(y);
	write (1, ",", 1);
	x = ft_itoa(c->p.x);
	if (!x)
		return ;
	write (1, x, ft_strlen(x));
	free(x);
	write (1, ")\n", 3);
	write (1, "\nstep ", 7);
	step = ft_itoa(i);
	if (!step)
		return ;
	write (1, step, ft_strlen(step));
	free(step);
	write (1, "\n", 2);
}

void	tty_print(t_mdata *f, t_lst *l, t_n *c, int i)
{
	unsigned long	area;
	unsigned long	sleep_time;
	unsigned long	max_sleep_time;
	int				x;

	x = -1;
	area = (unsigned long)f->mlw.x * (unsigned long)f->mlw.y;
	if (area > 0)
		sleep_time = 1000000000 / area;
	else
		sleep_time = 1000000000 / 1;
	max_sleep_time = 10000;
	if (sleep_time > max_sleep_time)
		sleep_time = max_sleep_time;
	usleep((useconds_t)sleep_time);
	if (i == 1)
		write (1, "\033[1JH", 6);
	print_nodes(f);
	print_lst(l);
	p_step_node(i, c);
	write (1, "\r", 2);
	if (l)
		while (++x < f->mlw.y + 5)
			write (1, "\033[A", 4);
}
