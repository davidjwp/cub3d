#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	printf("%i %i\n", dx, dy);
    int err = dx + dy, e2;

    while (1) {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

float degToRad(float degrees) {
    return degrees * (PI / 180.0);
}

//void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color) {
//    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//    int err = 2 * (dx - dy);
//	int	x = x0, y = y0;

//    while (x != x1 || y != y1) {
//        my_mlx_pixel_put(data, x, y, color);
//        printf ("x,y: %i||%i ", x, y);
//		if (err > 0) {y += sy; err -= 2 * dx;}
//		err += 2 * dy;
//		if (x != x1){x += sx;};
//    }
//}

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

int main() {
    t_data  img;
    img.mlx_ptr = mlx_init();
    img.win_ptr = mlx_new_window(img.mlx_ptr, WIDTH, HEIGHT, "Line Drawing");
    img.img_ptr = mlx_new_image(img.mlx_ptr, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_length, &img.endian);

    // Draw lines
    draw_line(&img, 150, 450, 150, 430, 0x00FF0000); // red line
    draw_line(&img, 0, 123, 453, 123, 0x0000FF00); // green line

	dot(&img, 0, 0);
    mlx_key_hook(img.win_ptr, close_win, &img);
    mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
    mlx_loop(img.mlx_ptr);

    return (0);
}
	//px = 150;
	//py = 400;
	//pa = 90;
	//pdx = 150;
	//pdy = 450 - LINE;