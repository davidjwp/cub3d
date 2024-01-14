/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:23:59 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 14:07:50 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	ptr_size;

	ptr_size = (int)(nmemb * size);
	if (size != 0 && nmemb != (size_t)ptr_size / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (ptr_size--)
		ptr[ptr_size] = 0;
	return (ptr);
}
