/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:47:04 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:10:15 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	a;

	a = 0;
	while (--n + 1)
	{
		*(unsigned char *)dest++ = *(unsigned char *)src++;
		a++;
	}
	while (a--)
		dest--;
	return (dest);
}
