/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:30:48 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:20:27 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		index;
	char	*bigp;

	index = 0;
	bigp = (char *)big;
	if (!*little)
		return ((char *)big);
	if (!len)
		return (0);
	while (len && *bigp != '\0')
	{
		while (*bigp == little[index] && len--)
		{
			bigp++;
			index++;
		}
		bigp -= index;
		if (little[index] == '\0')
			return (bigp);
		len += index;
		index = 0;
		bigp++;
		len--;
	}
	return (NULL);
}
