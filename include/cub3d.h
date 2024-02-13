/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:58:28 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/12 14:09:43 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <linux/limits.h>

# include "../libft/libft.h"
# include <mlx.h>
# include "structures.h"

/*=======================Parser=======================*/

/*		parser			*/
bool	file_parse(t_mdata *fdata);

/*		UtilsA			*/
bool	ismap(char c);
bool	ischar(char c);
bool	l_ismap(char *l);
bool	err_msg(const char *msg);
void	clean(t_mdata mdata);

/*		UtilsB			*/
int		gnl(int fd, char **str, int i, int n);
int		find_map(t_mdata *fdata, t_pos *p);
bool	is_full(char **map);
int		find_highest(int *index);

/*		UtilsC			*/
bool	l_issp(char	*map);
bool	free_lst(t_lst *l);
bool	find_nchar(t_n **start, t_mdata *f, t_pos *p);
bool	n_open(t_n **node, t_pos p, t_pos mlw);

/*		cr_map			*/
bool	cr_map(t_mdata *fdata);
bool	texcol_check(t_mdata *fd, int i, int y);

/*		cr_nodes		*/
bool	cr_nodes(t_mdata *fdata);
void	free_nodes(t_n **nodes, t_pos mlw, int index);

/*		Prints			*/
void	print_map(char **map);
void	tty_print(t_mdata *f, t_lst *l, t_n *c, int i);

/*=======================Renderer=======================*/

/*		Renderer		*/
int		start_renderer(t_mdata *fdata);

/*		Inits		*/
void	init_raycast(t_mlx *d, t_pos cpos);
bool	init_render(t_mlx *d, t_mdata *fdata);
void	init_hooks(t_mlx *d);

/*		get_texcol		*/
bool	xpm_check(t_mdata *d, t_mlx *m, void *mlx);
bool	col_check(t_mdata *d);

/*		Minimap			*/
void	minimap(t_mlx *d, t_ray *r);

/*		UtilsA			*/
bool	outmap(t_pos start, t_minline mini);
void	swap_buffers(t_mlx *data);
void	pixput(t_img *i, int x, int y, int color);
void	drawstrip(t_img *i, int x, int *y, int color);

/*		raycast			*/
void	raycast(t_mlx *d, t_ray *r);
void	drawplayer(t_mlx *d, int x, int y);
void	caldrawstrip(t_mlx *d, t_ray *r, int x);

/*		raycalc_utils			*/
void	rayinit(int x, t_ray *r);
void	stepcal(t_ray *r);
void	raydda(t_mlx *d, t_ray *r);

/*=======================Controls=======================*/

/*		hook_functions	*/
int		mouse(int mouseX, int mouseY, t_mlx *d);
int		key_press(int key, void *param);
int		key_release(int key, void *param);

/*		exit_game		*/
int		close_win(void *param);

/*		move_player		*/
int		buttons(t_mlx *d);

/*		rotate_player	*/
void	rotate_right(t_ray *r);
void	rotate_left(t_ray *r);

#endif
