/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsC.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:39:02 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/20 22:50:48 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_highest(int *index)
{
	int	highest;
	int	y;
	int	i;

	y = -1;
	i = -1;
	highest = 0;
	while (++y < 2)
		while (++i < 6)
			if (index[i] > highest)
				highest = index[i];
	return (highest);
}

bool	l_issp(char	*map)
{
	int	i;

	i = 0;
	while (map[i] == ' ' || map[i] == '\t')
		i++;
	if (!map[i] || *map == '\n')
		return (true);
	return (false);
}

bool	free_lst(t_lst *l)
{
	t_lst	*f;

	if (!l)
		return (false);
	while (l->next != NULL)
	{
		f = l;
		l = l->next;
		free(f);
	}
	free(l);
	return (false);
}