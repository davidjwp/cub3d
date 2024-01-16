/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:26:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/16 18:51:49 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	bool	s;
	int		i;

	s = false;
	i = -1;
	if (!l)
		return (false);
	while (l[++i])
	{
		if (ismap(l[i]))
			s = true;
		if (!ismap(l[i]) && (!s && (l[i] == 32 || l[i] == 9)))
			return (false);
	}
	return (true);
}

bool	err_msg(const char *msg)
{
	write(2, "Error: ", 8);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}

void	clean_all(char *buf, t_mdata mdata, int fd)
{
	free(buf);
	free_split(mdata.map, 0);
	free_split(mdata.tex, 0);
	close(fd);
}
