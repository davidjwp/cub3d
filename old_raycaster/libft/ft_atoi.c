/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:42:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/30 14:40:36 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	negative;	

	result = 0;
	negative = 1;
	while (*nptr && ((*nptr >= 9 && *nptr <= 13) || *nptr == 32 ))
		nptr++;
	if (!(*nptr))
		return (-1);
	if (*nptr == '-')
	{
		nptr++;
		negative = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += *nptr - 48;
		nptr++;
	}
	result *= negative;
	return (result);
}
