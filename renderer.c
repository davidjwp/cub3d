/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:31:29 by djacobs           #+#    #+#             */
/*   Updated: 2024/02/05 15:48:07 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc renderer.c -o render -I./minilibx-linux -L./minilibx-linux -lmlx -lX11 -lXext -lm
#include "include/cub3d.h"

// #define WIDTH 1024
// #define HEIGHT 512
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF
#define GREEN 0x0000FF00
#define DGREEN 0x0000B500
#define BLUE 0x000000FF
#define XWALL 0x00EAE9D9
#define YWALL 0x00D5D3BD
#define SKY	0x0032BEC7
#define GROUND 0x0027C650



#define FOV 60
#define NUM_RAYS 60

float	rdx, rdy;

float	ry, rx;

int	ray = 0;

int	lastMouseX, lastMouseY;//mouse coordinates

// int	mapX = 8, mapY = 8;

void swap_buffers(t_mlx *d) {
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i->img[d->i->current], 0, 0);
	d->i->current = !d->i->current; // Swap buffer index
	mlx_destroy_image(d->mlx, d->i->img[d->i->current]); // Destroy the old buffer
	d->i->img[d->i->current] = mlx_new_image(d->mlx, WIDTH / 2, HEIGHT); // Create a new buffer
	d->i->add[d->i->current] = mlx_get_data_addr(d->i->img[d->i->current], &d->i->bpp, &d->i->len, &d->i->end);
	//usleep(1);
	if (d->win != NULL)
		mlx_put_image_to_window(d->mlx, d->win, d->i3D->img[d->i3D->current], HEIGHT, 0);
	d->i3D->current = !d->i3D->current; // Swap buffer index
	mlx_destroy_image(d->mlx, d->i3D->img[d->i3D->current]); // Destroy the old buffer
	d->i3D->img[d->i3D->current] = mlx_new_image(d->mlx, WIDTH / 2, HEIGHT); // Create a new buffer
	d->i3D->add[d->i3D->current] = mlx_get_data_addr(d->i3D->img[d->i3D->current], &d->i3D->bpp, &d->i3D->len, &d->i3D->end);
}

void init_images(t_mlx *d) {
	for (int i = 0; i < 2; i++) {
		d->i->img[i] = mlx_new_image(d->mlx, WIDTH / 2, HEIGHT);
		d->i->add[i] = mlx_get_data_addr(d->i->img[i], &d->i->bpp, &d->i->len, &d->i->end);
	}
	for (int i = 0; i < 2; i++){
		d->i3D->img[i] = mlx_new_image(d->mlx, WIDTH / 2, HEIGHT);
		d->i3D->add[i] = mlx_get_data_addr(d->i3D->img[i], &d->i3D->bpp, &d->i3D->len, &d->i3D->end);		
	}
	d->i->current = 0;
	d->i3D->current = 0;
}

void pixPut(t_img *i, int x, int y, int color)//keep this 
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = i->add[i->current] + (y * i->len + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void pixPut3D(t_mlx *d, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		int pixelPos = y * d->i3d->len + x * (d->i3d->bpp / 8);
		char *dst = d->i3d->add[d->i3d->current] + pixelPos;
		*(unsigned int*)dst = color;
	}
}

#define SPOS 8.5//strip position
#define SWID 7.6//strip thickness

void drawVerticalSegment(t_mlx *d, float lineHeight, int color) {
	float drawStart = -lineHeight / 2 + HEIGHT / 2;
	if (drawStart < 0) drawStart = 0;
	float drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

	for (float i = 0.0; i < SWID; i+=0.1){
		for (float y = drawStart; y < (drawEnd); y++) {
			pixPut3D(d, ((ray * SPOS) + (WIDTH / 64) - 14.5) + i, y, color);
		}
	}
}
void	draw3Dmap(t_mlx *d, float x, float y, float ra, float odX, float odY, int color)
{
	(void) odX;
	(void) odY;
	float dist = sqrt((x - d->pl->px) * (x - d->pl->px) + (y - d->pl->py) * (y - d->pl->py));
	float correctedDist = dist * cos(degtorad(ra - d->pl->pa)); // 'ra' is the ray's angle, 'pa' is the player's angle
	float lineHeight = HEIGHT / correctedDist;

	drawVerticalSegment(d, lineHeight * 64, color);
}

void drawLineDDA(t_mlx *d, int x1, int y1, int x2, int y2, int color, float ra) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	int steps = fmax(abs(dx), abs(dy));

	float xIncrement = dx / (float)steps;
	float yIncrement = dy / (float)steps;

	float x = x1;
	float y = y1;

	for (int i = 0; i <= steps; i++) {
		pixPut(d, round(x), round(y), color);
		if (d->map[abs((int)y / MAPS)][abs((int)x / MAPS)] == '1') {draw3Dmap(d, x, y, ra, dx, dy, DGREEN);break;}
		if (x1 == x2 && y1 == y2) break;
		x += xIncrement;
		y += yIncrement;
	}
}

//bresenham draw
int drawLine(t_mlx *d, int x0, int y0, int x1, int y1, int color, float ra)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1) {
		pixPut(d, x0, y0, color);
		if (d->map[(abs(y0 / MAPS))][abs(x0 / MAPS)] == '1') {draw3Dmap(d, x0, y0, ra, dx, dy, color);break;}
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; if (d->map[(abs(y0 / MAPS))][abs(x0 / MAPS)] == '1') color = YWALL	;}
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
	return (0);
}

void bresCast(t_mlx *d) {
	float angleStep = FOV / NUM_RAYS; // Define FOV and NUM_RAYS as needed
	float rayAngle = d->pl->pa - (FOV / 2);
	float odX;
	float odY;

	for (float i = 0; i < NUM_RAYS; i++) {
		if (i) {rdx = odX - (d->pl->px + LINE * cos(degtorad(rayAngle)));
				rdy = odY - (d->pl->py + LINE * sin(degtorad(rayAngle)));}
		else {	rdx = d->pl->px + LINE * cos(degtorad(rayAngle));
				rdy = d->pl->py + LINE * sin(degtorad(rayAngle));}
		// Calculate ray direction
		odX = d->pl->px + LINE * cos(degtorad(rayAngle));
		odY = d->pl->py + LINE * sin(degtorad(rayAngle));

		// Cast the ray and draw the 3D view
		drawLine(d, d->pl->px, d->pl->py, odX, odY, XWALL, rayAngle);
		//drawLineDDA(data, d->pl->px, d->pl->py, odX, odY, GREEN, rayAngle);
		rayAngle += angleStep;
		ray++;
	}
	ray = 0;
}

void	drawBackground(t_mlx *d)
{
	for (int i = 0; i < HEIGHT; i++) 
		for (int j = 0; j < WIDTH / 2; j++) 
			pixPut(d->i, j, i, 0x00808080);
}

void	drawNode(t_mlx *d, int size, int y, int x, int color)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			pixPut(d->i, j + x, i + y, color);
}

void	drawMap(t_mlx *d)
{

	for (int i = 0; i < d->mxy.y; i++){
		for(int y = 0; y < d->mxy.x; y++){
			if (d->map[i][y]=='1')
				drawNode(d, MAPS - 2, i * MAPS, y * MAPS, WHITE);
			else
				drawNode(d, MAPS - 2, i * MAPS, y * MAPS, 0x00000000);
		}
	}
}

void drawPlayer(t_mlx *d)
{
	t_p	s = (t_p){px- 4, py- 4};
	t_p	e = (t_p){s.x+8,s.y+8};

	while (s.y < e.y){
		while (s.x < e.x){
			pixPut(d->i, s.x, s.y, YELLOW);
			s.x++;
		}
		s.x = px - 4;
		s.y++;
	}
}

void	drawTopBot(t_mlx *d)
{
	for (int y = 0;y < HEIGHT / 2; y++){
		for (int x = 0; x < WIDTH / 2; x++)
			pixPut3D(d, x, y, d->col[1]);
	}
	for (int y = 0;y < HEIGHT / 2; y++){
		for (int x = 0; x < WIDTH / 2; x++)
			pixPut3D(d, x, y + (HEIGHT / 2), d->col[0]);
	}
}

void	display(t_mlx *d)
{
	//if (pass < 2 || d->k->d || d->k->a || d->k->w || d->k->s)
	//{
	swap_buffers(d);
	drawBackground(d);
	drawMap(d);
	drawPlayer(d, d->pl->py, d->pl->px);
	drawTopBot(d);
	bresCast(d);
	//drawLine(d,px ,py,d->pl->pdx,d->pl->pdy,BLUE, pa);
	//pass++;
	//}
}

int	mouse(int mouseX, int mouseY, t_mlx *d)
{
	(void) mouseY;
	if (d->k->mouse == false)
	{
		if (mouseX > WIDTH / 2)
		rotate_right(d);
		if (mouseX < WIDTH / 2)
		rotate_left(d);
		mlx_mouse_move(d->mlx, d->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

int	buttons(t_mlx *d)
{
	if (d->k->w && check_collision_ws('w', d))
		move_forward(d);
	if (d->k->s && check_collision_ws('s', d))
		move_backwards(d);
	if (d->k->a && check_collision_da('a', d))
		move_left(d);
	if (d->k->d && check_collision_da('d', d))
		move_right(d);
	display(d);
	return (0);
}

void	destroyAll(t_mlx *d, t_mdata *fdata){
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(d->mlx, d->i->img[i]);
	for (int i = 0;i < 2; i++)
		mlx_destroy_image(d->mlx, d->i3d->img[i]);
	for (int i = 0; i < 4; i++)
		mlx_destroy_image(d->mlx, fdata->xpms[i]);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	//free(d->k);
	free(d->i);
	free(d->i3d);
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
	d.mxy = fdata->mlw;
	d.i = malloc(sizeof(t_img));
	d.i3D = malloc(sizeof(t_img));
	d.k = malloc(sizeof(t_key));
	d.pl = malloc(sizeof(t_pld));
	d.pl->px = (fdata->cpos.x * MAPS) + (MAPS / 2);
	d.pl->py = (fdata->cpos.y * MAPS) + (MAPS / 2);
	d.pl->pa = 0;
	d.pl->pdx = d.pl->px + LINE;
	d.pl->pdy = d.pl->py;
	lastMouseX = 512;
	lastMouseY = 255;
	d.k->a = false;
	d.k->w = false;
	d.k->d = false;
	d.k->s = false;
	d.k->p = false;
	d.k->mouse = false;
	d.k->ra = false;
	d.k->la = false;

/*			initialization				*/
	d.mlx = mlx_init();
	
	if (!xpm_check(fdata, d.mlx))
		return (err_msg("Bad textures"), mlx_destroy_display(d.mlx), free(d.mlx),free(d.i),free(d.i3d),free(d.k), -1);
	if (!col_check(fdata))
		return (mlx_destroy_display(d.mlx), free(d.mlx), free(d.i),free(d.i3d),free(d.k), -1);
	d.col[0] = fdata->col[0];
	d.col[1] = fdata->col[1];
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "window");
	init_images(&d);
	// mlx_mouse_hide(d.mlx, d.win);
	mlx_hook(d.win, KeyPress, KeyPressMask, key_press, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, key_release, &d);
	mlx_hook(d.win, MotionNotify, PointerMotionMask, mouse, &d);
	mlx_loop_hook(d.mlx, buttons, &d);
	//display(&d);

	mlx_loop(d.mlx);
/*				clean up				*/
	destroyAll(&d, fdata);
	return (0);
}
