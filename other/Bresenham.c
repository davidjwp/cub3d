#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846
#define LINE 100

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
} t_data;

float px,pdx,py,pdy;

float angle;


void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    if (x < WIDTH && y < HEIGHT)
        *(unsigned int*)dst = color;
}

void draw_line(t_data *data, int color) {
    int dx = abs(pdx - px), sx = px < pdx ? 1 : -1;
    int dy = -abs(pdy - py), sy = py < pdy ? 1 : -1;
    int err = dx + dy, e2;
    int x = px, y = py;

    while (1) {
        my_mlx_pixel_put(data, x, y, color);
        if (x == pdx && y == pdy) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x += sx; }
        if (e2 <= dx) { err += dx; y += sy; }
    }
}

void	dot(t_data *t, int x, int y)
{
	for (int a = 0; a < 8; a++){
		for (int b = 0; b < 8; b++){
			my_mlx_pixel_put(t, x + a, y + b, 0x0000FF00);
		}
	}
}

int close_win(int key, void *param)
{
    if (key == XK_Escape)
    {
        t_data *i = (t_data *)param;
        mlx_destroy_image(i->mlx_ptr, i->img_ptr);
        mlx_destroy_window(i->mlx_ptr, i->win_ptr);
        mlx_loop_end(i->mlx_ptr);
    }
}

int degToRad(float a) {return (a * PI) / 180.0;}

void rotate(void) {
    if (angle >= 360)
        angle = 0;

    // Assuming originalX0, originalY0, originalX1, and originalY1 store the original line coordinates
    float rad = degToRad(angle);

    // Translate points to origin
    float translatedX0 = 100 - (px - LINE);
    float translatedY0 = 100 - (py - LINE);
    float translatedX1 = 200 - (px - LINE);
    float translatedY1 = 200 - (py - LINE);

    // Rotate points
    px = translatedX0 * cos(rad) - translatedY0 * sin(rad) + (px - LINE);
    py = translatedX0 * sin(rad) + translatedY0 * cos(rad) + (py - LINE);
    pdx = translatedX1 * cos(rad) - translatedY1 * sin(rad) + (px - LINE);
    pdy = translatedX1 * sin(rad) + translatedY1 * cos(rad) + (py - LINE);

    angle += 0.1;
}

//void    rotate(void)
//{
//    if (angle >= 360)
//        angle = 0;
//    float   originx = px - LINE;
//    float   originy = px - LINE;
//    px += cos(degToRad(angle));
//    py += sin(degToRad(angle));
//    pdx += cos(degToRad(angle));
//    pdy += sin(degToRad(angle));
//    angle += 1.5;
//}

int render(void *param)
{
    t_data  *img = (t_data *)param;

    printf("before: %.1f||%.1f\t%.1f||%.1f\n", px, py, pdx, pdy);
    rotate();
    printf("after: %.1f||%.1f\t%.1f||%.1f\n", px, py, pdx, pdy);
    draw_line(img, 0x0000FF00);
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
}


int main() {
    t_data  img;
    img.mlx_ptr = mlx_init();
    img.win_ptr = mlx_new_window(img.mlx_ptr, WIDTH, HEIGHT, "Line Drawing");
    img.img_ptr = mlx_new_image(img.mlx_ptr, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_length, &img.endian);
    px = 100, pdx = px + LINE, py = 100, pdy = py + LINE;
    angle = 45;

    // Draw lines
    //draw_line(&img, 150, 450, 150, 430, 0x00FF0000); // red line
    //draw_line(&img, 0, 123, 453, 123, 0x0000FF00); // green line

	dot(&img, 0, 0);
    mlx_key_hook(img.win_ptr, close_win, &img);
    mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
    mlx_loop_hook(img.mlx_ptr, render, &img);
    mlx_loop(img.mlx_ptr);

    return (0);
}