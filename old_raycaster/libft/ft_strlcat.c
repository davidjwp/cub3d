/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:47:51 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:17:30 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_lenght;
	size_t			src_lenght;
	unsigned int	index;

	index = 0;
	dst_lenght = ft_strlen(dst);
	src_lenght = ft_strlen(src);
	if (size <= dst_lenght)
		return (src_lenght + size);
	while (src[index] && index < size - dst_lenght - 1)
	{	
		dst[dst_lenght + index] = src[index];
		index++;
	}
	dst[dst_lenght + index] = '\0';
	return (dst_lenght + src_lenght);
}
