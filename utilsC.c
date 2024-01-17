/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsC.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:39:02 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/17 18:02:48 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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