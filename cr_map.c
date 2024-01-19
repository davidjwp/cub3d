/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:07:46 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/19 18:08:24 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	texcol_check(t_mdata *fd, int i, int y)
{
	char	*tex[5];
	int		pos;

	while (++i < 7)
		tex[i] = (char *[7]){"NO ./", "SO ./", "WE ./", "EA ./", "F ", \
		"C ", NULL}[i];
	y = 0;
	while (fd->map[y])
	{
		if (!is_full(fd->tex) && texcol(&pos, fd, y, tex) && pos <= 3)
			ft_strlcpy(fd->tex[pos], ft_strchr(fd->map[y], '/') + 1, \
			ft_strlen(ft_strchr(fd->map[y], '/') + 1) + 1);
		if (!is_full(fd->tex) && texcol(&pos, fd, y, tex) && pos > 3)
			ft_strlcpy(fd->tex[pos], ft_strchr(fd->map[y], ' ') + 1, \
			ft_strlen(ft_strchr(fd->map[y], ' ') + 1) + 1);
		y++;
	}
	if (is_full(fd->tex))
		return (trim(fd));
	return (false);
}

//start searching the map from the position of the last color of texture
bool	cr_map(t_mdata *fdata)
{
	char	**tmp;
	int		len;
	t_pos	p;
	int		i;

	i = -1;
	p = (t_pos){-1, -1};
	len = find_map(fdata, &p) + 1;
	if (p.y < 0 || p.y < find_highest(fdata->tc_index))
		return (false);
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (err_msg("cr_map malloc fail"));
	tmp[len - 1] = NULL;
	while (--len)
	{
		tmp[++i] = malloc(sizeof(char) * (ft_strlen(fdata->map[p.y]) + 1));
		if (!tmp[i])
			return (free_split(tmp, i), err_msg("cr_map index malloc fail"));
		ft_strlcpy(tmp[i], fdata->map[p.y], ft_strlen(fdata->map[p.y]) + 1);
		p.y++;
	}
	free_split(fdata->map, 0);
	fdata->map = tmp;
	return (true);
}
