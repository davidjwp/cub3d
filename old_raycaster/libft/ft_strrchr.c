/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:15:42 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:21:02 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sp;
	int		index;

	index = 0;
	sp = (char *)s;
	while (sp[index])
		index++;
	while (index >= 0)
	{
		if ((char)c == sp[index])
			return (sp + index);
		index--;
	}
	return (0);
}
