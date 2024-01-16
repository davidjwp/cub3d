/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:26:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/16 14:27:36 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	i;

	i = -1;
	while (l[++i])
		if (ismap(l[i]))
			return (true);
	return (false);
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
