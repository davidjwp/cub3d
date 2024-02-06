/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:17:17 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:05:31 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scast;

	scast = (unsigned char *)s;
	if (!n)
		return (NULL);
	while (scast < (scast + n) && n--)
	{
		if (*scast == (unsigned char)c)
			return (scast);
		scast++;
	}
	return (NULL);
}
