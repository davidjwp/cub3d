/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:29:50 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 19:19:44 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*mapi;

	index = 0;
	mapi = ft_strdup(s);
	while (mapi[index])
	{
		mapi[index] = (*f)(index, mapi[index]);
		index++;
	}
	return (mapi);
}
