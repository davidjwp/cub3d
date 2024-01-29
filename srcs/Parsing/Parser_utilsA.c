/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_utilsA.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:26:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/29 16:46:01 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	0 is empty
	1 is a wall
	N is the player facing North
	S is the player facing South
	E is the player facing East
	W is the player facing West
*/

bool	ismap(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	ischar(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	l_ismap(char *l)
{
	int		i;

	if (!l)
		return (false);
	if (l_issp(l))
		return (false);
	i = -1;
	while (l[++i])
		if (!ismap(l[i]) && l[i] != 32 && l[i] != 9)
			return (false);
	return (true);
}

bool	err_msg(const char *msg)
{
	write(2, "\033[101mError\033[0m\n", 17);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}

void	clean_all(char *buf, t_mdata mdata, int fd)
{
	free(buf);
	free_split(mdata.map, 0);
	free_split(mdata.tex, 0);
	if (mdata.m_nodes != NULL)
		free_nodes(mdata.m_nodes, mdata.mlw, 0);
	close(fd);
}
