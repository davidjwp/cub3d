/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/21 22:04:41 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc renderer.c -o render -I./minilibx-linux -L./minilibx-linux -lmlx -lX11 -lXext -lm
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>

#define WIDTH 1024
#define HEIGHT 512
#define YELLOW 0x00FFFF00

typedef struct s_img{
	void	*img;
	char	*add;
	int		bpp;
	int		len;
	int		end;
}t_img;

typedef struct s_key{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
}t_key;

typedef struct s_mlx{
	void	*mlx;
	void	*win;
	t_img	*i;
	t_key	*k;
}t_mlx;

//this map is already created in the main program btw
char map[][8] =	{{"11111111"},\
				 {"10100001"},\
				 {"10100001"},\
				 {"10100001"},\
				 {"10000001"},\
				 {"10000101"},\
				 {"10000001"},\
				 {"11111111"}};

float	px, py;//player position

int	lastMouseX, lastMouseY;//mouse coordinates

int	mapH = 8, mapW = 8, mapS = 64;

int	close_win(int key, void *param)
{
	t_mlx	*d;

	d = (t_mlx *)param;
	if (key == XK_Escape){
		mlx_destroy_window(d->mlx, d->win);
		mlx_loop_end(d->mlx);
		d->win = NULL;
	}
	return (0);
}

void drawNode(t_mlx *d, int size, int y, int x, int color)
{
	int	pixel;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			pixel = ((int)(y + i) * d->i->len + (int)(x + j) * \
			(d->i->bpp / 8));
			if (pixel >= 0 && pixel < WIDTH * HEIGHT * (d->i->bpp / 8)) 
				*(int *)(d->i->add + pixel) = color;
		}
	}
}

void	drawMap(t_mlx *d)
{

	for (int i = 0; i < mapH; i++){
		for(int y = 0; y < mapW; y++){
			if (map[i][y]=='1')
				drawNode(d, mapS, i * mapS, y * mapS, YELLOW);
			else
				drawNode(d, mapS, i * mapS, y * mapS, 0x00000000);
		}
	}
}

void drawPlayer(t_mlx *d)
{
	int	pixel;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pixel = ((int)(py + i) * d->i->len + (int)(px + j) * \
			(d->i->bpp / 8));
			if (pixel >= 0 && pixel < WIDTH * HEIGHT * (d->i->bpp / 8)) 
				*(int *)(d->i->add + pixel) = (int)YELLOW;
		}
	}
}

void	clear_buffer(t_mlx *d)
{
	int	color = 0x00000000;
	int	pixel;

	for (int i = 0; i < HEIGHT; i++) {
		for (int y = 0; y < WIDTH; y++) {
			pixel = (i * d->i->len + y * (d->i->bpp / 8));
			if (pixel >= 0 && pixel < WIDTH * HEIGHT * (d->i->bpp / 8)) 
				*(int *)(d->i->add + pixel) = color;
		}
	}
}

void	display(t_mlx *d)
{
	clear_buffer(d);
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i->img, 0, 0);
	drawMap(d);
	drawPlayer(d);
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i->img, 0, 0);
}

int	buttons(t_mlx *d)
{
	if (d->k->w){ py-=0.3;}
	if (d->k->s){ py+=0.3;}
	if (d->k->d){ px+=0.3;}
	if (d->k->a){ px-=0.3;}
	display(d);
}

int key_press(int key, void *param) {
    t_mlx	*d = (t_mlx *)param;

	if (key == XK_Escape){
    	close_win(key, param);
		return (0);
	}
	if (key == 'w') d->k->w = true;
    if (key == 'a') d->k->a = true;
    if (key == 's') d->k->s = true;
    if (key == 'd') d->k->d = true;
	return (0);
}

// Update this function to unset the key flags
int key_release(int key, void *param) {
    t_mlx	*d = (t_mlx *)param;
	
	if (key == 'w') d->k->w = false;
    if (key == 'a') d->k->a = false;
    if (key == 's') d->k->s = false;
    if (key == 'd') d->k->d = false;
    return (0);
}


int	main(void)
{
	t_mlx	d;

	d.i = malloc(sizeof(t_img));
	d.k = malloc(sizeof(t_key));
	px = 300;
	py = 300;
	lastMouseX = 512;
	lastMouseX = 255;
	d.k->a = false;
	d.k->w = false;
	d.k->d = false;
	d.k->s = false;

/*			initialization				*/
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	d.i->img = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	d.i->add = mlx_get_data_addr(d.i->img, &d.i->bpp, &d.i->len, &d.i->end);

	mlx_hook(d.win, KeyPress, KeyPressMask, key_press, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, key_release, &d);
	mlx_loop_hook(d.mlx, buttons, &d);
	display(&d);



	mlx_loop(d.mlx);
/*				clean up				*/
	mlx_destroy_image(d.mlx, d.i->img);
	mlx_destroy_display(d.mlx);
	free(d.k);
	free(d.i);
	free(d.mlx);
	return (0);
}