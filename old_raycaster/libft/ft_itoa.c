/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:33:12 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 12:08:09 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlength(int n)
{
	int	length;

	length = 1;
	if (n <= 0)
		length++;
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*res_char;
	unsigned int	length;

	length = nlength(n);
	res_char = (char *)ft_calloc(length, sizeof(char));
	if (!res_char)
		return (NULL);
	length--;
	if (n == -2147483648 && length--)
	{
		res_char[0] = '-';
		res_char[length] = '8';
		n = (n + -1) / 10;
	}
	if (n < 0)
	{
		res_char[0] = '-';
		n *= -1;
	}
	while (length-- && res_char[length] != '-')
	{	
		res_char[length] = n % 10 + 48;
		n /= 10;
	}
	return (res_char);
}
