/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:49 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/26 17:08:09 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//main will have to be changed later on
int	main(void)
{
	//mlx_t		*mlx;
	//mlx_image_t	*image;
	
	t_mdata		fdata;
	const char	*file_name;
	int			fd;
	char		*buf;

	/*			initialization			*/

	//mlx initialization
	//mlx = mlx_init(WIDTH, HEIGHT, "window", true);
	//if (!mlx)
	//	return (err_msg("mlx init fail"), -1);

	//main data structure
	fdata = (t_mdata){NULL, NULL, NULL, {0, 0, 0, 0, 0, 0}, {0, 0}, NULL};
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
	
	//opening files
	file_name = "Map.cub";
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (err_msg("open fail"), 1);
	
	//getting file content
	if (gnl(fd, &buf, 0, 0))
		return (err_msg("gnl error"), close(fd), 2);
	if (buf == NULL)
		return (err_msg("gnl fail"), close(fd), 3);
	
	/*			parsing					*/
	if (file_parse(ft_split(buf, '\n'), file_name, &fdata))
		printf("\033[102mgood Map\033[0m\n");
	else
		printf("\033[101mbad Map\033[0m\n");
	print_map(fdata.map);
	/*			cleaning up				*/
	clean_all(buf, fdata, fd);
	
	/*			mlx loop				*/
	//mlx_loop(mlx);
	//mlx_terminate(mlx);
	return (1);
}