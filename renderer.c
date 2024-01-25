/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/01/25 03:00:52 by djacobs          ###   ########.fr       */
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
#define LINE 25
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF

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
}t_key;

typedef struct s_mlx{
	void	*mlx;
	void	*win;
	t_img	*i;
	t_key	*k;
}t_mlx;

#define PI 3.14159
#define MAPS 64
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

int	lastMouseX, lastMouseY;//mouse coordinates

int	mapX = 8, mapY = 8;

int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}//keeps the angle withing 360
float degToRad(int a) { return a*PI/180.0;}//converts an angle to a radian for cos and sin functions

void swap_buffers(t_mlx *data) {
    if (data->win != NULL)
		mlx_put_image_to_window(data->mlx, data->win, data->i->img[data->i->current], 0, 0);
    data->i->current = !data->i->current; // Swap buffer index
    mlx_destroy_image(data->mlx, data->i->img[data->i->current]); // Destroy the old buffer
    data->i->img[data->i->current] = mlx_new_image(data->mlx, WIDTH, HEIGHT); // Create a new buffer
    data->i->add[data->i->current] = mlx_get_data_addr(data->i->img[data->i->current], &data->i->bpp, &data->i->len, &data->i->end);
}

void init_images(t_mlx *data) {
    for (int i = 0; i < 2; i++) {
        data->i->img[i] = mlx_new_image(data->mlx, WIDTH, HEIGHT);
        data->i->add[i] = mlx_get_data_addr(data->i->img[i], &data->i->bpp, &data->i->len, &data->i->end);
    }
    data->i->current = 0;
}

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

void pixPut(t_mlx *d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		int pixelPos = y * d->i->len + x * (d->i->bpp / 8);
		char *dst = d->i->add[d->i->current] + pixelPos;
		*(unsigned int*)dst = color;
	}
}

int drawLine(t_mlx *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
		pixPut(data, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void	rayCastDDA(t_mlx *data)
{
	   float ra = pa; // Ray angle

    // Calculate ray direction components
    float dx = cos(degToRad(ra));
    float dy = sin(degToRad(ra));

    // DDA initialization
    float xStep, yStep;
    int mapCheckX, mapCheckY;
    float sideDistX, sideDistY;
    float deltaDistX = (dx == 0) ? 1e30 : fabs(1 / dx);
    float deltaDistY = (dy == 0) ? 1e30 : fabs(1 / dy);
    float perpWallDist;

    int stepX, stepY;
    int hit = 0;
    int side;

    // Calculate step direction and initial distances to a side
    if (dx < 0) {
        stepX = -1;
        sideDistX = (px - (int)px) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = ((int)px + 1.0 - px) * deltaDistX;
    }
    if (dy < 0) {
        stepY = -1;
        sideDistY = (py - (int)py) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = ((int)py + 1.0 - py) * deltaDistY;
    }

    // Perform DDA
    mapCheckX = (int)px;
    mapCheckY = (int)py;
    while (hit == 0) {
        // Jump to next map square in x or y direction
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapCheckX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapCheckY += stepY;
            side = 1;
        }
        // Check if the ray has hit a wall
        if (mapCheckX >= 0 && mapCheckX < mapX && mapCheckY >= 0 && mapCheckY < mapY) {
            if (map[mapCheckY][mapCheckX] == '1') hit = 1;
        } else {
            hit = 1; // Consider out of bounds as a 'hit' to stop the ray
        }
    }

    // Calculate distance to the point of impact
    if (side == 0) perpWallDist = (mapCheckX - px + (1 - stepX) / 2) / dx;
    else perpWallDist = (mapCheckY - py + (1 - stepY) / 2) / dy;

    // Draw the ray in the 2D map
    int lineEndX = px + perpWallDist * dx;
    int lineEndY = py + perpWallDist * dy;
    drawLine(data, px, py, lineEndX, lineEndY, YELLOW);
}

//void	rayCast(t_mlx *data)
//{
//	float	ra,rx,ry,rdx,rdy, xo, yo;
//	int		r,mx,my,mp,dof;
//	fmax

//	ra=pa;
//	for (r=0;r<1;r++)
//	{
//		dof=0;
//		float aTan=-1/tan(degToRad(ra));
//		if (ra>PI){ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;}
//		if (ra<PI){ry=(((int)py>>6)<<6)+64; rx=(py-ry)*aTan+px; yo=64; xo=-yo*aTan;}
//		if (ra==0 || ra==PI){rx=px; ry=py;dof=8;}
//		while(dof<8){ 
//			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
//			if(mp>0 && mp<mapX*mapY && map[mp]=='1'){ dof=8;}//hit         
//			else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
//		}
//		drawLine(data, px, py, rx, ry, YELLOW);
//	}
//}


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
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i->img[d->i->current], 0, 0);
	//printf("px:%.1f||py:%.1f||pa:%.1f\tpdx:%.1f||pdy:%.1f\n", px, py, pa, pdx, pdy);
	drawBackground(d);
	drawMap(d);
	drawPlayer(d, py, px);
	drawLine(d,px ,py,pdx,pdy,YELLOW);
	rayCastDDA(d);
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i->img[d->i->current], 0, 0);
	swap_buffers(d);
}


int	buttons(t_mlx *d)
{
	if (d->k->a){pa+=5; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->d){pa-=5; pa=FixAng(pa);pdx=px + LINE * cos(degToRad(pa)); pdy= py + LINE * sin(degToRad(pa));}
	if (d->k->w){px+=cos(degToRad(pa)) * 1.5; py+=sin(degToRad(pa)) * 1.5;pdx+=cos(degToRad(pa)) * 1.5; pdy+=sin(degToRad(pa)) * 1.5;}
	if (d->k->s){px-=cos(degToRad(pa)) * 1.5; py-=sin(degToRad(pa)) * 1.5;pdx-=cos(degToRad(pa)) * 1.5; pdy-=sin(degToRad(pa)) * 1.5;}
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

void	destroyAll(t_mlx *d){
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(d->mlx, d->i->img[i]);
    mlx_destroy_display(d->mlx);
    free(d->mlx);
	free(d->k);
	free(d->i);
}

int	main(void)
{
	t_mlx	d;

	d.i = malloc(sizeof(t_img));
	d.k = malloc(sizeof(t_key));
	px=150.0; py=400.0; pa=0;
	pdx=px+LINE, pdy=py;
	lastMouseX = 512;
	lastMouseY = 255;
	d.k->a = false;
	d.k->w = false;
	d.k->d = false;
	d.k->s = false;

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