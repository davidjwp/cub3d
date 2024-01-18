/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:17:57 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/18 19:37:35 by djacobs          ###   ########.fr       */
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

static void	_pNode(t_nodes node)
{
	if (node.s)
		write (1, " ", 1);
	else if (node.w)
		write (1, "1", 1);
	else 
		write (1, "0", 1);
}

void	PrintNodes(t_mdata *f)
{
	for (int i = 0; i <= f->mlw.y; i++)
		for(int y = 0; y <= f->mlw.x; y++)
			y == f->mlw.x ? write (1, "\n", 1) : _pNode(f->m_nodes[i][y]);
}