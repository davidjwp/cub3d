/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:28:01 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:10:48 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	a;
	unsigned char	*destcast;
	unsigned char	*srccast;

	destcast = (unsigned char *)dest;
	srccast = (unsigned char *)src;
	a = 0;
	if (dest > src)
	{	
		while (n--)
			destcast[n] = srccast[n];
	}
	else
	{	
		while (a < n)
		{
			destcast[a] = srccast[a];
			a++;
		}
	}
	return (dest);
}
