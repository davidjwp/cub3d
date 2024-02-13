/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:49 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/10 16:40:05 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//valgrind --leak-check=full --show-leak-kinds=all --suppressions=minimal.supp

bool	mdata_init(t_mdata *md, char *filename)
{
	char	*buf;
	int		fd;

	*md = (t_mdata){NULL, {NULL, NULL, NULL, NULL, NULL, NULL, NULL}, NULL, \
	{0, 0, 0, 0, 0, 0}, {-1, -1}, {0, 0}, {0, 0}, '0'};
	if (ft_strncmp(ft_strchr(filename, '.'), ".cub", 5))
		return (err_msg("Bad extension"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (err_msg("open fail"));
	if (gnl(fd, &buf, 0, 0))
		return (close(fd), err_msg("gnl error"));
	if (buf == NULL)
		return (close(fd), err_msg("gnl fail"));
	md->map = ft_split(buf, '\n');
	if (!md->map)
		return (close(fd), err_msg("mdata_init split fail"));
	free(buf);
	close(fd);
	return (true);
}

int	main(int ac, char **av)
{
	t_mdata		md;

	if (ac == 1)
		err_msg("Please provide a map!");
	else if (ac == 2)
	{
		if (!mdata_init(&md, av[1]))
			return (-1);
		if (file_parse(&md))
			printf("\033[102mgood Map\033[0m\n\n");
		else
			return (printf("\033[101mbad Map\033[0m\n\n"), clean(md), -1);
		start_renderer(&md);
		clean(md);
	}
	else if (ac >= 3)
		err_msg("Too many Arguments!");
	return (1);
}
