/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/26 16:41:51 by djacobs          ###   ########.fr       */
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
#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 512
#define LINE 500
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

typedef struct s_p{
	float	x;
	float	y;
}t_p;

typedef struct s_img{
	void	*img[2];
	char	*add[2];
	int		bpp;
	int		len;
	int		end;
	int		current;
}t_img;

typedef struct s_key{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	p;
}t_key;

typedef struct s_mlx{
	void	*mlx;
	void	*win;
	t_img	*i3D;
	t_img	*i;
	t_key	*k;
}t_mlx;

#define PI 3.14159
#define MAPS 64
#define RS (float)0.5
#define MS 1
//this map is already created in the main program btw
char map[][8] =	{{"11111111"},\
				 {"10100001"},\
				 {"10100001"},\
				 {"10100001"},\
				 {"10000001"},\
				 {"10000101"},\
				 {"10000001"},\
				 {"11111111"}};

float	px, py, pa;//point position/angle

float	pdx, pdy;//delta point

float	ry, rx;

int	ray = 0;

int	lastMouseX, lastMouseY;//mouse coordinates

int	mapX = 8, mapY = 8;

float FixAng(float a){if(a>359){ a-=360;}if(a<0){ a+=360;}return a;}//keeps the angle withing 360
float degToRad(int a) { return a*PI/180.0;}//converts an angle to a radian for cos and sin functions

int	close_win(int key, void *param)
{
	t_mlx	*d;

	d = (t_mlx *)param;
	if (key == XK_Escape){
		mlx_loop_end(d->mlx);
		mlx_destroy_window(d->mlx, d->win);
		d->win = NULL;
	}
	return (0);
}

void swap_buffers(t_mlx *data) {
    if (data->win != NULL)
		mlx_put_image_to_window(data->mlx, data->win, data->i->img[data->i->current], 0, 0);
    data->i->current = !data->i->current; // Swap buffer index
    mlx_destroy_image(data->mlx, data->i->img[data->i->current]); // Destroy the old buffer
    data->i->img[data->i->current] = mlx_new_image(data->mlx, WIDTH, HEIGHT); // Create a new buffer
	if (data->win != NULL)
		mlx_put_image_to_window(data->mlx, data->win, data->i3D->img[data->i3D->current], 512, 0);
    data->i->add[data->i->current] = mlx_get_data_addr(data->i->img[data->i->current], &data->i->bpp, &data->i->len, &data->i->end);
    data->i3D->current = !data->i3D->current; // Swap buffer index
    mlx_destroy_image(data->mlx, data->i3D->img[data->i3D->current]); // Destroy the old buffer
    data->i3D->img[data->i3D->current] = mlx_new_image(data->mlx, WIDTH, HEIGHT); // Create a new buffer
    data->i3D->add[data->i3D->current] = mlx_get_data_addr(data->i3D->img[data->i3D->current], &data->i3D->bpp, &data->i3D->len, &data->i3D->end);
}

void init_images(t_mlx *data) {
    for (int i = 0; i < 2; i++) {
        data->i->img[i] = mlx_new_image(data->mlx, WIDTH, HEIGHT);
        data->i->add[i] = mlx_get_data_addr(data->i->img[i], &data->i->bpp, &data->i->len, &data->i->end);
    }
	for (int i =0; i < 2; i++){
		data->i3D->img[i] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT / 2);
		data->i3D->add[i] = mlx_get_data_addr(data->i3D->img[i], &data->i3D->bpp, &data->i3D->len, &data->i3D->end);		
	}
    data->i->current = 0;
	data->i3D->current = 0;
}

void pixPut(t_mlx *d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		int pixelPos = y * d->i->len + x * (d->i->bpp / 8);
		char *dst = d->i->add[d->i->current] + pixelPos;
		*(unsigned int*)dst = color;
	}
}

void pixPut3D(t_mlx *d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		int pixelPos = y * d->i3D->len + x * (d->i3D->bpp / 8);
		char *dst = d->i3D->add[d->i3D->current] + pixelPos;
		*(unsigned int*)dst = color;
	}
}

void drawVerticalSegment(t_mlx *data, int lineHeight, int color) {
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
	if (data->k->p)
		printf("ray%i\theight:%i\tdrawdelta%i\n", ray, lineHeight, abs(drawStart - drawEnd));

    for (int i = 0; i < 8; i++){
		for (int y = drawStart; y < drawEnd; y++) {
	        pixPut3D(data, (ray + (i)) + (WIDTH / 4), y, color); 
	    }
	} 
}

void	draw3Dmap(t_mlx *data, float x, float y, float ra, int color)
{
	float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
	//float correctedDist = dist * -cos(ra - pa); // 'ra' is the ray's angle, 'pa' is the player's angle
	int lineHeight = (int)(HEIGHT / dist);


	drawVerticalSegment(data, abs(lineHeight * 32), color);
	//if (data->k->p)
	//	printf ("ray:%i\theight:%i\tdist:%.1f\n", ray, lineHeight, dist);
}

//bresenham draw
int drawLine(t_mlx *data, int x0, int y0, int x1, int y1, int color, float ra)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
		pixPut(data, x0, y0, color);
        if (map[(abs(y0 / MAPS))][abs(x0 / MAPS)] == '1' || x0 == x1 && y0 == y1){draw3Dmap(data, x0, y0, ra, color);break;}
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
#define FOV 60
#define NUM_RAYS 60

void bresCast(t_mlx *data) {
    float angleStep = FOV / NUM_RAYS; // Define FOV and NUM_RAYS as needed
    float rayAngle = pa - (FOV / 2);

    for (int i = 0; i < NUM_RAYS; i++) {
        // Calculate ray direction
        float odX = px + LINE * cos(degToRad(rayAngle));
        float odY = py + LINE * sin(degToRad(rayAngle));

        // Cast the ray and draw the 3D view
        drawLine(data, px, py, odX, odY, GREEN, rayAngle);
        rayAngle += angleStep;
		ray++;
    }
	ray = 0;
}

void	drawBackground(t_mlx *d)
{
	int	pixel;

	for (int i = 0; i < HEIGHT; i++) 
		for (int j = 0; j < WIDTH; j++) 
			pixPut(d, j, i, 0x00808080);
}

void	drawNode(t_mlx *d, int size, int y, int x, int color)
{
	int	pixel;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			pixPut(d, j + x, i + y, color);
}

void	drawMap(t_mlx *d)
{

	for (int i = 0; i < mapY; i++){
		for(int y = 0; y < mapX; y++){
			if (map[i][y]=='1')
				drawNode(d, MAPS - 2, i * MAPS, y * MAPS, WHITE);
			else
				drawNode(d, MAPS - 2, i * MAPS, y * MAPS, 0x00000000);
		}
	}
}

void drawPlayer(t_mlx *d, int y, int x)
{
	t_p	s = (t_p){x-4,y-4};
	t_p	e = (t_p){s.x+8,s.y+8};

	while (s.y < e.y){
		while (s.x < e.x){
			pixPut(d, s.x, s.y, YELLOW);
			s.x++;
		}
		s.x = x - 4;
		s.y++;
	}
}

void	display(t_mlx *d)
{
	//if (d->win != NULL) mlx_put_image_to_window(d->mlx, d->win, d->i->img[d->i->current], 0, 0);
	//printf("px:%.1f||py:%.1f||pa:%.1f\tpdx:%.1f||pdy:%.1f\n", px, py, pa, pdx, pdy);
	drawBackground(d);
	drawMap(d);
	drawPlayer(d, py, px);
	bresCast(d);
	drawLine(d,px ,py,pdx,pdy,BLUE, pa);
	swap_buffers(d);
}


int	buttons(t_mlx *d)
{
	if (d->k->d){pa+=RS; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->a){pa-=RS; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->w){px+=cos(degToRad(pa)) * MS; py+=sin(degToRad(pa)) * MS;pdx+=cos(degToRad(pa)) * MS; pdy+=sin(degToRad(pa)) * MS;}
	if (d->k->s){px-=cos(degToRad(pa)) * MS; py-=sin(degToRad(pa)) * MS;pdx-=cos(degToRad(pa)) * MS; pdy-=sin(degToRad(pa)) * MS;}
	//printf("pa:%.1f\n", (pa+=RS, pa=FixAng(pa)));
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
	if (key == 'p') d->k->p = true;
	return (0);
}

// Update this function to unset the key flags
int key_release(int key, void *param) {
    t_mlx	*d = (t_mlx *)param;
	
	if (key == 'w') d->k->w = false;
    if (key == 'a') d->k->a = false;
    if (key == 's') d->k->s = false;
    if (key == 'd') d->k->d = false;
	if (key == 'p') d->k->p = false;
    return (0);
}

void	destroyAll(t_mlx *d){
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(d->mlx, d->i->img[i]);
	for (int i = 0;i < 2; i++)
		mlx_destroy_image(d->mlx, d->i3D->img[i]);
    mlx_destroy_display(d->mlx);
    free(d->mlx);
	free(d->k);
	free(d->i);
	free(d->i3D);
}

int	main(void)
{
	t_mlx	d;

	d.i = malloc(sizeof(t_img));
	d.i3D = malloc(sizeof(t_img));
	d.k = malloc(sizeof(t_key));
	px=150.0; py=400.0; pa=0;
	pdx=px+LINE, pdy=py;
	lastMouseX = 512;
	lastMouseY = 255;
	d.k->a = false;
	d.k->w = false;
	d.k->d = false;
	d.k->s = false;
	d.k->p = false;

/*			initialization				*/
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	init_images(&d);

	mlx_hook(d.win, KeyPress, KeyPressMask, key_press, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, key_release, &d);
	mlx_loop_hook(d.mlx, buttons, &d);
	display(&d);

	mlx_loop(d.mlx);
/*				clean up				*/
	destroyAll(&d);
	return (0);
}