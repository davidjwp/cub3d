/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:56:59 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/15 21:09:53 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft/libft.h"
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

int	gnl(int fd, char **str, int i, int n)
{
	char	*buf;
	char	c;

	buf = malloc(sizeof(char) * BUF_SIZ);
	if (buf == NULL)
		return (*str = NULL, 1);
	n = read(fd, &c, 1);
	if (n == 0 || n == -1)
		return (free(buf), err_msg("gnl read fail"), *str = NULL, 2);
	while (c == '\n')
		n = read(fd, &c, 1);
	if (n)
		buf[i++] = c;
	while (n && c != 0)
	{
		n = read(fd, &c, 1);
		if (i == BUF_SIZ - 1)
			break ;
		if (n != 0)
			buf[i] = c;
		i++;
	}
	buf[i - 1] = 0;
	buf[BUF_SIZ - 1] = 0;
	return (*str = buf, 0);
}
