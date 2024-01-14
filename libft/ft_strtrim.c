/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:05:59 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 13:20:43 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trim;
	unsigned int	length;
	unsigned int	index;

	index = 0;
	length = 0;
	while (is_set(*s1, set))
		s1++;
	if (*s1)
	{
		while (s1[length])
			length++;
		while (is_set(s1[length - 1], set))
			length--;
	}
	trim = (char *)malloc(sizeof(char) * (length + 1));
	while (length--)
		trim[index++] = *s1++;
	trim[index] = 0;
	return (trim);
}
