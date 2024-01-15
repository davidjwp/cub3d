/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:31:10 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/15 18:11:15 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//modified split added security
void	free_split(char **split, int index)
{
	if (!index)
	{
		while (split[index] != NULL)
			free(split[index++]);
	}
	else
	{
		while (index)
		{
			free(split[index]);
			index--;
		}	
	}
	free(split);
}

static char	*ft_word_cpy(char const *s, char c)
{
	char	*word_cpy;
	int		word_len;
	int		index;

	word_len = 0;
	while (s[word_len] != c && s[word_len])
		word_len++;
	word_cpy = (char *)malloc(word_len + 1);
	index = 0;
	while (index < word_len)
	{
		word_cpy[index] = *s++;
		index++;
	}
	word_cpy[index] = '\0';
	return (word_cpy);
}

static int	ft_word_count(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			return (word_count);
		word_count++;
		while (*s != c && *s)
			s++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		index;

	index = 0;
	split = (char **)ft_calloc((ft_word_count(s, c) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			split[index] = ft_word_cpy(s, c);
			if (!split[index])
				return (free_split(split, index), NULL);
		}
		index++;
		while (*s != c && *s)
			s++;
	}
	return (split);
}
