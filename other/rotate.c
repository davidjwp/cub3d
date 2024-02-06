#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846

typedef struct s_data {
    void    *mlx;
    void    *win;
	void	*img[2];
    char    *addr[2];
    int     bpp;
    int     line_length;
    int     endian;
	int		current;
    float   angle;
    float   x0, y0, x1, y1;  // Line endpoints
} t_data;

// Convert degrees to radians
float degToRad(float degrees) {
    return degrees * (PI / 180.0);
}

void init_images(t_data *data) {
    for (int i = 0; i < 2; i++) {
        data->img[i] = mlx_new_image(data->mlx, WIDTH, HEIGHT);
        data->addr[i] = mlx_get_data_addr(data->img[i], &data->bpp, &data->line_length, &data->endian);
    }
    data->current = 0;
}

void swap_buffers(t_data *data) {
    mlx_put_image_to_window(data->mlx, data->win, data->img[data->current], 0, 0);
    data->current = !data->current; // Swap buffer index
    mlx_destroy_image(data->mlx, data->img[data->current]); // Destroy the old buffer
    data->img[data->current] = mlx_new_image(data->mlx, WIDTH, HEIGHT); // Create a new buffer
    data->addr[data->current] = mlx_get_data_addr(data->img[data->current], &data->bpp, &data->line_length, &data->endian);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int pixelPos = y * data->line_length + x * (data->bpp / 8);
        char *dst = data->addr[data->current] + pixelPos;
        *(unsigned int*)dst = color;
    }
}

int lineDDA(t_data *d, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = fmax(abs(dx), abs(dy));

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(d, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}
//int mlx_line_put(t_data *data, int x0, int y0, int x1, int y1, int color) {
//    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//    int err = dx + dy, e2;

//    while (1) {
//		my_mlx_pixel_put(data, x0, y0, color);
//        if (x0 == x1 && y0 == y1) break;
//        e2 = 2 * err;
//        if (e2 >= dy) { err += dy; x0 += sx; }
//        if (e2 <= dx) { err += dx; y0 += sy; }
//    }
//}

// Draw a line on the window
void draw_line(t_data *data) {
    //mlx_clear_window(data->mlx, data->win);

    //mlx_line_put(data, data->x0, data->y0, data->x1, data->y1, 0x00FFFFFF);  // White line
    lineDDA(data, data->x0, data->y0, data->x1, data->y1, 0x00FFFFFF);

	//mlx_put_image_to_window(data->mlx, data->win, data->img, 0,0);
	//clear_buffer(data);
}

// Rotate the line
void rotate_line(t_data *data) {
    float rad = degToRad(data->angle);
    float pivotX = WIDTH / 2, pivotY = HEIGHT / 2;  // Pivot at the center of the window

    // Define original line endpoints relative to the pivot
    float originalX0 = -100, originalY0 = 0;
    float originalX1 = 100, originalY1 = 0;

    // Rotate points
    data->x0 = originalX0 * cos(rad) - originalY0 * sin(rad) + pivotX;
    data->y0 = originalX0 * sin(rad) + originalY0 * cos(rad) + pivotY;
    data->x1 = originalX1 * cos(rad) - originalY1 * sin(rad) + pivotX;
    data->y1 = originalX1 * sin(rad) + originalY1 * cos(rad) + pivotY;

    // Increment angle
    data->angle += 0.1;
    if (data->angle >= 360.0) data->angle = 0.0;
}

void    drawdots(t_data *data)
{
    for (int i =0; i < 4; i++)
        for (int y=0; y < 4; y++)
            my_mlx_pixel_put(data, data->x0 + y + i, data->y0 + y + i, 0x00FFFF00);
    for (int i =0; i < 4; i++)
        for (int y=0; y < 4; y++)
            my_mlx_pixel_put(data, data->x1 + y + i, data->y1 + y + i, 0x00FFFF00);
}

int loop_hook(void *param) {
    t_data *data = param;
    rotate_line(data);
    draw_line(data);
    //drawdots(data);
	//swap_buffers(data);
    return (0);
}

int	closeWin(int key, void *param)
{
	t_data	*d = (t_data *)param;

	if (key == XK_Escape)
		mlx_loop_end(d->mlx);
}

void	destroyAll(t_data *d){
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(d->mlx, d->img[i]);
	mlx_destroy_window(d->mlx, d->win);
    mlx_destroy_display(d->mlx);
    free(d->mlx);
}


int main() {
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Spinning Line");
	init_images(&data);
	data.angle = 0.0;

	mlx_key_hook(data.win, closeWin, &data);
    mlx_loop_hook(data.mlx, loop_hook, &data);
    mlx_loop(data.mlx);
	destroyAll(&data);
    return 0;
}
