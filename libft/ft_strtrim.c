/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:05:59 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/15 19:23:24 by djacobs          ###   ########.fr       */
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

//modified
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
	if (!trim)
		return (NULL);
	while (length--)
		trim[index++] = *s1++;
	trim[index] = 0;
	return (trim);
}
