/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:42:28 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 18:42:52 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	negative;	

	result = 0;
	negative = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
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
