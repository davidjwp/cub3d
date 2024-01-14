/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:55:00 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:15:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		index;

	index = 0;
	duplicate = malloc(ft_strlen((char *)s) + 1);
	if (!duplicate)
		return (0);
	while (s[index])
	{
		duplicate[index] = s[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}
