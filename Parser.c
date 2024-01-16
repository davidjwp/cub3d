/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:21:47 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/16 14:23:50 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//gcc -g3 -Wall -Werror -Wextra Parser.c utils.c -L -llibft libft/libft.a
/*
*	Checks for spaces and tabs before the textures and colors then trims tabs
*	and spaces off the end of the string.
*
*	Returns a boolean value
*/
bool	trim(t_mdata *md)
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

bool	texcol(int *pos, t_mdata *fd, int y, char **tex)
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

	printf("HERE\n");
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


//bool	cr_map(t_mdata *fdata, t_pos p)
//{
//	while (fdata->map[p.y])
//	{
//		while (fdata->map[p.y][p.x])
//			if (ischar(fdata->map[p.y][p.x++]) && !is_texcol(p.y, fdata))
//		p.x = 0;
//		p.y++;
//	}



//	while (l_ismap(fdata->map[p.x]))
//		p.x--;
//	p.x++;
//	while (l_ismap(fdata->map[p.x]))
//		p.x--;
//}

bool	file_parse(char **split, const char *file_name, t_mdata *fdata)
{
	if (split == NULL)
		return (err_msg("split fail"));
	fdata->map = split;
	if (ft_strncmp(ft_strchr(file_name, '.'), ".cub", 5))
		return (err_msg("Bad extension"));
	if (!texcol_check(fdata, -1, 0))
		return (err_msg("Bad texcol"));
	//if (!cr_map(fdata, (t_pos){0, 0}))
	//	return (false);
	return (true);
}

int	main(void)
{
	t_mdata		fdata;
	const char	*file_name;
	int			fd;
	char		*buf;

	/*			initialization			*/
	fdata = (t_mdata){NULL, NULL, {0, 0, 0, 0, 0, 0}};
	fdata.tex = malloc(sizeof(char *) * 7);
	if (!fdata.tex)
		return (err_msg("malloc fail"), -1);
	for (int i = 0; i < 6; i++){
		fdata.tex[i] = malloc(sizeof(char) * BUF_SIZ);
		if (!fdata.tex[i])
			return (err_msg("malloc fail"), free_split(fdata.tex, i), -1);
		*fdata.tex[i] = 0;
	}
	fdata.tex[6] = NULL;
	file_name = "Map.cub";
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (err_msg("open fail"), 1);
	if (gnl(fd, &buf, 0, 0))
		return (err_msg("gnl error"), close(fd), 2);
	if (buf == NULL)
		return (err_msg("gnl fail"), close(fd), 3);
	/*			parsing					*/
	if (file_parse(ft_split(buf, '\n'), file_name, &fdata))
		printf("good Map\n");
	else
		printf("bad Map\n");
	/*			cleaning up				*/
	clean_all(buf, fdata, fd);
	return (0);
}
