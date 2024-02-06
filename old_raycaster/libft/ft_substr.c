/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:34:43 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:22:07 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	unsigned int	sublen;
	char			*substr;

	index = start;
	sublen = 0;
	while (index < ft_strlen(s) && index < (start + len))
	{
		index++;
		sublen++;
	}
	substr = (char *)ft_calloc(sublen + 1, sizeof(char));
	if (!substr)
		return (NULL);
	index = 0;
	while (sublen)
	{
		substr[index] = s[start];
		start++;
		index++;
		sublen--;
	}
	return (substr);
}
