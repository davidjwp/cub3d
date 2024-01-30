/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/30 21:08:45 by djacobs          ###   ########.fr       */
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
#include "include/cub3d.h"

// #define WIDTH 1024
// #define HEIGHT 512
#define LINE 1500
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF
#define GREEN 0x0000FF00
#define DGREEN 0x0000B500
#define BLUE 0x000000FF
#define XWALL 0x00EAE9D9
#define YWALL 0x00D5D3BD
#define SKY	0x0032BEC7
#define GROUND 0x0027C650

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

typedef struct s_3Dimg{
	void	*img[2];
	char	*add[2];
	int		bpp;
	int		len;
	int		end;
	int		current;
}t_3Dimg;

typedef struct s_mlx{
	void	*mlx;
	void	*win;
	char	**map;
	int		mapX;
	int		mapY;
	t_img	*i3D;
	t_img	*i;
	t_key	*k;
}t_mlx;

#define PI 3.14159
#define MAPS 64
#define RS (float)1.2
#define MS 1
//this map is already created in the main program btw

float	px, py, pa;//point position/angle

float	pdx, pdy;//delta point

float	rdx, rdy;

float	ry, rx;

int	ray = 0;

int	lastMouseX, lastMouseY;//mouse coordinates

// int	mapX = 8, mapY = 8;

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
	data->i->img[data->i->current] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT); // Create a new buffer
	data->i->add[data->i->current] = mlx_get_data_addr(data->i->img[data->i->current], &data->i->bpp, &data->i->len, &data->i->end);
	//usleep(1);
	if (data->win != NULL)
		mlx_put_image_to_window(data->mlx, data->win, data->i3D->img[data->i3D->current], HEIGHT, 0);
	data->i3D->current = !data->i3D->current; // Swap buffer index
	mlx_destroy_image(data->mlx, data->i3D->img[data->i3D->current]); // Destroy the old buffer
	data->i3D->img[data->i3D->current] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT); // Create a new buffer
	data->i3D->add[data->i3D->current] = mlx_get_data_addr(data->i3D->img[data->i3D->current], &data->i3D->bpp, &data->i3D->len, &data->i3D->end);
}

void init_images(t_mlx *data) {
	for (int i = 0; i < 2; i++) {
		data->i->img[i] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT);
		data->i->add[i] = mlx_get_data_addr(data->i->img[i], &data->i->bpp, &data->i->len, &data->i->end);
	}
	for (int i = 0; i < 2; i++){
		data->i3D->img[i] = mlx_new_image(data->mlx, WIDTH / 2, HEIGHT);
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
	//if (!ray)
	//	printf("(int)x:%i\n", x);
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		int pixelPos = y * d->i3D->len + x * (d->i3D->bpp / 8);
		char *dst = d->i3D->add[d->i3D->current] + pixelPos;
		*(unsigned int*)dst = color;
	}
}

#define SPOS 8.5//strip position
#define SWID 7.6//strip thickness

void drawVerticalSegment(t_mlx *data, float lineHeight, int color) {
	float drawStart = -lineHeight / 2 + HEIGHT / 2;
	if (drawStart < 0) drawStart = 0;
	float drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

	for (float i = 0.0; i < SWID; i+=0.1){
		for (float y = drawStart; y < (drawEnd); y++) {
			pixPut3D(data, ((ray * SPOS) + (WIDTH / 64) - 14.5) + i, y, color);
		}
	}
}
void	draw3Dmap(t_mlx *data, float x, float y, float ra, float odX, float odY, int color)
{
	(void) odX;
	(void) odY;
	float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
	float correctedDist = dist * cos(degToRad(ra - pa)); // 'ra' is the ray's angle, 'pa' is the player's angle
	float lineHeight = HEIGHT / correctedDist;
	//float odist = sqrt(());
	//float codist = odist * cos(degToRad(ra - pa));
	//float nlH = HEIGHT / codist;


	drawVerticalSegment(data, lineHeight * 64, color);
}

void drawLineDDA(t_mlx *data, int x1, int y1, int x2, int y2, int color, float ra) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	int steps = fmax(abs(dx), abs(dy));

	float xIncrement = dx / (float)steps;
	float yIncrement = dy / (float)steps;

	float x = x1;
	float y = y1;

	for (int i = 0; i <= steps; i++) {
		pixPut(data, round(x), round(y), color);
		if (data->map[abs((int)y / MAPS)][abs((int)x / MAPS)] == '1') {draw3Dmap(data, x, y, ra, dx, dy, DGREEN);break;}
		if (x1 == x2 && y1 == y2) break;
		x += xIncrement;
		y += yIncrement;
	}
}

//bresenham draw
int drawLine(t_mlx *data, int x0, int y0, int x1, int y1, int color, float ra)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1) {
		pixPut(data, x0, y0, color);
		if (data->map[(abs(y0 / MAPS))][abs(x0 / MAPS)] == '1') {draw3Dmap(data, x0, y0, ra, dx, dy, color);break;}
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; if (data->map[(abs(y0 / MAPS))][abs(x0 / MAPS)] == '1') color = YWALL	;}
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
	return (0);
}

#define FOV 60
#define NUM_RAYS 60

void bresCast(t_mlx *data) {
	float angleStep = FOV / NUM_RAYS; // Define FOV and NUM_RAYS as needed
	float rayAngle = pa - (FOV / 2);
	float odX;
	float odY;

	for (float i = 0; i < NUM_RAYS; i++) {
		if (i) {rdx = odX - (px + LINE * cos(degToRad(rayAngle)));
				rdy = odY - (py + LINE * sin(degToRad(rayAngle)));}
		else {	rdx = px + LINE * cos(degToRad(rayAngle));
				rdy = py + LINE * sin(degToRad(rayAngle));}
		// Calculate ray direction
		odX = px + LINE * cos(degToRad(rayAngle));
		odY = py + LINE * sin(degToRad(rayAngle));

		// Cast the ray and draw the 3D view
		drawLine(data, px, py, odX, odY, XWALL, rayAngle);
		//drawLineDDA(data, px, py, odX, odY, GREEN, rayAngle);
		rayAngle += angleStep;
		ray++;
	}
	ray = 0;
}

void	drawBackground(t_mlx *d)
{
	for (int i = 0; i < HEIGHT; i++) 
		for (int j = 0; j < WIDTH / 2; j++) 
			pixPut(d, j, i, 0x00808080);
}

void	drawNode(t_mlx *d, int size, int y, int x, int color)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			pixPut(d, j + x, i + y, color);
}

void	drawMap(t_mlx *d)
{

	for (int i = 0; i < d->mapY; i++){
		for(int y = 0; y < d->mapX; y++){
			if (d->map[i][y]=='1')
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

void	drawTopBot(t_mlx *d)
{
	for (int y = 0;y < HEIGHT / 2; y++){
		for (int x = 0; x < WIDTH / 2; x++)
			pixPut3D(d, x, y, SKY);
	}
	for (int y = 0;y < HEIGHT / 2; y++){
		for (int x = 0; x < WIDTH / 2; x++)
			pixPut3D(d, x, y + (HEIGHT / 2), DGREEN);
	}
}

void	display(t_mlx *d)
{
	//if (pass < 2 || d->k->d || d->k->a || d->k->w || d->k->s)
	//{
	swap_buffers(d);
	drawBackground(d);
	drawMap(d);
	drawPlayer(d, py, px);
	drawTopBot(d);
	bresCast(d);
	//drawLine(d,px ,py,pdx,pdy,BLUE, pa);
	//pass++;
	//}
}


int	buttons(t_mlx *d)
{
	if (d->k->d){pa+=RS; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->a){pa-=RS; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->w){px+=cos(degToRad(pa)) * MS; py+=sin(degToRad(pa)) * MS;pdx+=cos(degToRad(pa)) * MS; pdy+=sin(degToRad(pa)) * MS;}
	if (d->k->s){px-=cos(degToRad(pa)) * MS; py-=sin(degToRad(pa)) * MS;pdx-=cos(degToRad(pa)) * MS; pdy-=sin(degToRad(pa)) * MS;}
	display(d);
	return (0);
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

void	destroyAll(t_mlx *d, t_mdata *fdata){
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(d->mlx, d->i->img[i]);
	for (int i = 0;i < 2; i++)
		mlx_destroy_image(d->mlx, d->i3D->img[i]);
	for (int i = 0; i < 4; i++)
		mlx_destroy_image(d->mlx, fdata->xpms[i]);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	free(d->k);
	free(d->i);
	free(d->i3D);
}

bool	xpm_check(t_mdata *d, void *mlx)
{
	d->xpms[NO] = mlx_xpm_file_to_image(mlx, d->tex[NO], \
	&d->iwh[NO].x, &d->iwh[NO].y);
	if (d->xpms[NO] == NULL)
		return (false);
	d->xpms[SO] = mlx_xpm_file_to_image(mlx, d->tex[SO], \
	&d->iwh[SO].x, &d->iwh[SO].y);
	if (d->xpms[SO] == NULL)
		return (mlx_destroy_image(mlx, d->xpms[NO]), false);
	d->xpms[WE] = mlx_xpm_file_to_image(mlx, d->tex[WE], \
	&d->iwh[WE].x, &d->iwh[WE].y);
	if (d->xpms[WE] == NULL)
		return (mlx_destroy_image(mlx, d->xpms[NO]), \
		mlx_destroy_image(mlx, d->xpms[SO]), false);
	d->xpms[EA] = mlx_xpm_file_to_image(mlx, d->tex[EA], \
	&d->iwh[EA].x, &d->iwh[EA].y);
	if (d->xpms[EA] == NULL)
		return (mlx_destroy_image(mlx, d->xpms[NO]), \
		mlx_destroy_image(mlx, d->xpms[SO]), \
		mlx_destroy_image(mlx, d->xpms[EA]), false);
	return (true);
}

static bool	rgb(char **s, unsigned *r, unsigned *g, unsigned *b)
{
	if (s == NULL)
		return (err_msg("rgb_to_hex split fail"));
	if (s[0] == NULL || s[1] == NULL || s[2] == NULL ||\
		*s[0] == ',' || *s[1] == ',' || *s[2] == ',')
		return (free_split(s, 0), err_msg("Colors missing or empty values"));
	*r = ft_atoi(s[0]);
	*g = ft_atoi(s[1]);
	*b = ft_atoi(s[2]);
	return (free_split(s, 0), true);
}

bool	rgb_to_hex(t_mdata *d)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!rgb(ft_split(d->tex[F], ','), &r, &g, &b))
		return (false);
	if (b > 255 || g > 255 || r > 255)
		return (err_msg("Floor values too high"));
	d->col[0] = (r << 16) | (g << 8) | b;
	if (!rgb(ft_split(d->tex[C], ','), &r, &g, &b))
		return (false);
	if (b > 255 || g > 255 || r > 255)
		return (err_msg("Floor values too high"));
	d->col[1] = (r << 16) | (g << 8) | b;
	return (true);
}

bool	col_check(t_mdata *d)
{
	t_pos	p;

	p = (t_pos){-1, -1};
	while (++p.y < 2)
	{
		while (d->tex[F + p.y][++p.x])
			if (d->tex[F + p.y][p.x] != 44 && d->tex[F + p.y][p.x] != 32 && \
			d->tex[F + p.y][p.x] != 9 && !ft_isdigit(d->tex[F + p.y][p.x]))
				return (err_msg("Bad col input"), false);
		p.x = -1;
	}
	if (!rgb_to_hex(d))
		return (false);
	return (true);
}

int	start_renderer(t_mdata *fdata)
{
	t_mlx	d;

	d.map = fdata->map;
	d.mapX = fdata->mlw.x;
	d.mapY = fdata->mlw.y;
	d.i = malloc(sizeof(t_img));
	d.i3D = malloc(sizeof(t_img));
	d.k = malloc(sizeof(t_key));
	px = (fdata->cpos.x * MAPS) + (MAPS / 2); py = (fdata->cpos.y * MAPS) + (MAPS / 2); pa=0;
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
	if (!xpm_check(fdata, d.mlx))
		return (err_msg("Bad textures"), mlx_destroy_display(d.mlx), free(d.mlx),free(d.i),free(d.i3D),free(d.k), -1);
	if (!col_check(fdata))
		return (mlx_destroy_display(d.mlx), free(d.mlx), free(d.i),free(d.i3D),free(d.k), -1);
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	init_images(&d);

	mlx_hook(d.win, KeyPress, KeyPressMask, key_press, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, key_release, &d);
	mlx_loop_hook(d.mlx, buttons, &d);
	display(&d);

	mlx_loop(d.mlx);
/*				clean up				*/
	destroyAll(&d, fdata);
	return (0);
}
