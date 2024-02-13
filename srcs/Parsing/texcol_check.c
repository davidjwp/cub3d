/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texcol_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:46:18 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 20:45:55 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
*	Checks for spaces and tabs before the textures and colors then trims tabs
*	and spaces off the end of the string.
*
*	Returns a boolean value
*/
static bool	trim(t_mdata *md)
{
	void	*tmp;
	int		i;

	i = -1;
	while (md->tex[++i] != NULL)
		if (*md->tex[i] == ' ' || *md->tex[i] == '\t')
			return (false);
	i = 0;
	while (md->tex[i] != NULL)
	{
		tmp = md->tex[i];
		md->tex[i] = ft_strtrim((md->tex[i]), " \t");
		if (!md->tex[i])
			return (md->tex[i] = tmp, err_msg("trim malloc fail"), false);
		free(tmp);
		i++;
	}
	return (true);
}

//compares the line with the texture id
static bool	texcol(int *pos, t_mdata *fd, int y, char **tex)
{
	*pos = 0;
	while (tex[*pos] != NULL)
	{
		if (!ft_strncmp(fd->map[y], tex[*pos], ft_strlen(tex[*pos])))
			return (fd->tc_index[*pos] = y, true);
		*pos += 1;
	}
	return (false);
}

static const char	*begtex(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != 9 && s[i] != 32)
			return (&s[i]);
	return (s);
}

//static bool	order(char **tex)
//{
//	int		i;
//	bool	s;

//	i = 7;
//	s = false;
//	while (--i)
//	{
//		if (tex[i] != NULL)
//			s = true;
//		if (tex[i] == NULL && s)
//			return (err_msg("Bad texture order"));
//	}
//	return (true);
//}

//the textures and colors and store them in the structure
bool	texcol_check(t_mdata *fd, int i, int y)
{
	char	*tex[5];
	int		pos;

	while (++i < 7)
		tex[i] = (char *[7]){"NO", "SO", "WE", "EA", "F ", \
		"C ", NULL}[i];
	while (fd->map[y])
	{
		//if (!order(fd->tex))
		//	break ;
		if (!is_full(fd->tex) && texcol(&pos, fd, y, tex) && pos <= 3 && \
		!fd->tex[pos])
			fd->tex[pos] = ft_strdup(begtex(&fd->map[y][0] + 2));
		if (!is_full(fd->tex) && texcol(&	pos, fd, y, tex) && pos > 3 && \
		!fd->tex[pos])
			fd->tex[pos] = ft_strdup(begtex(&fd->map[y][0] + 1));
		y++;
	}
	if (is_full(fd->tex))
		return (trim(fd));
	return (false);
}
